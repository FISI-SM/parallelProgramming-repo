/* ------------------------------------------------------------------------
 * ARCHIVO: minimos_cuadrados.c
 *
 * DESCRIPCION DEL PROBLEMA:
 *  El metodo de minimos cuadrados es una tecnica estandar utilizada para encontrar
 *  la ecuacion de una linea recta a partir de un conjunto de datos. La ecuacion para una
 *  linea recta esta dada por
 *	 y = mx + b
 *  donde m es la pendiente de la linea y b es la interseccion con el eje y.
 *
 *  Dado un conjunto de n puntos {(x1,y1), x2,y2),...,xn,yn)}, sea
 *      SUMAx = x1 + x2 + ... + xn
 *      SUMAy = y1 + y2 + ... + yn
 *      SUMAxy = x1*y1 + x2*y2 + ... + xn*yn
 *      SUMAxx = x1*x1 + x2*x2 + ... + xn*xn
 *
 *  La pendiente e interseccion con y para la linea de minimos cuadrados puede entonces ser
 *  calculada usando las siguientes ecuaciones:
 *        pendiente (m) = ( SUMAx*SUMAy - n*SUMAxy ) / ( SUMAx*SUMAx - n*SUMAxx )
 *  interseccion-y (b) = ( SUMAy - pendiente*SUMAx ) / n
 *
 * DESCRIPCION DEL PROGRAMA:
 *  o Este programa calcula un modelo lineal para un conjunto de datos dados.
 *  o Los datos se leen desde un archivo; la primera linea es el numero de puntos
 *    de datos (n), seguido por las coordenadas de x e y.
 *  o Los puntos de datos se dividen entre procesos de tal manera que cada proceso
 *    tiene promedio_n = n/numero_procesos puntos; los puntos de datos restantes se
 *    agregan al ultimo proceso.
 *  o Cada proceso calcula las sumas parciales (miSUMAx,miSUMAy,miSUMAxy,
 *    miSUMAxx) independientemente, usando su subconjunto de datos. En el paso final,
 *    las sumas globales (SUMAx,SUMAy,SUMAxy,SUMAxx) se calculan para encontrar
 *    la linea de minimos cuadrados.
 *  o Para el proposito de este ejercicio, la comunicacion se hace estrictamente
 *    usando las operaciones punto a punto de MPI, MPI_SEND y MPI_RECV.
 *
 * USO: Probado para ejecutar usando 1,2,...,10 procesos.
 *
 * AUTOR: Dora Abdullah (version MPI, 11/96)
 * ULTIMA REVISION: RYL convertido a C (12/11)
 * ---------------------------------------------------------------------- */
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv) {

  double *x, *y;
  double miSUMAx, miSUMAy, miSUMAxy, miSUMAxx, SUMAx, SUMAy, SUMAxy,
         SUMAxx, SUMAresidual, residual, pendiente, interseccion_y, y_estimado;
  int i,j,n,mi_id,numero_procesos,promedio_n,n_restante,mis_puntos,desplazamiento_i;
  /*int pausa_personalizada (int segundos);*/
  MPI_Status estado_i;
  FILE *archivo_entrada;

  archivo_entrada = fopen("datos_xy.txt", "r");
  if (archivo_entrada == NULL) printf("error abriendo archivo\n");

  MPI_Init(&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &mi_id);
  MPI_Comm_size (MPI_COMM_WORLD, &numero_procesos);

  /* ----------------------------------------------------------
   * Paso 1: El proceso 0 lee datos y envia el valor de n
   * ---------------------------------------------------------- */
  if (mi_id == 0) {
    printf ("Numero de procesos utilizados: %d\n", numero_procesos);
    printf ("-------------------------------------\n");
    printf ("Las coordenadas x en los procesos trabajadores:\n");
    /* esta llamada se usa para lograr un formato de salida consistente */
    /* pausa_personalizada (3);*/
    fscanf (archivo_entrada, "%d", &n);
    x = (double *) malloc (n*sizeof(double));
    y = (double *) malloc (n*sizeof(double));
    for (i=0; i<n; i++)
      fscanf (archivo_entrada, "%lf %lf", &x[i], &y[i]);
    for (i=1; i<numero_procesos; i++)
      MPI_Send (&n, 1, MPI_INT, i, 10, MPI_COMM_WORLD);
  }
  else {
    MPI_Recv (&n, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &estado_i);
    x = (double *) malloc (n*sizeof(double));
    y = (double *) malloc (n*sizeof(double));
  }
  /* ---------------------------------------------------------- */
  
  promedio_n = n/numero_procesos;
  n_restante = n % numero_procesos;

  /* ----------------------------------------------------------
   * Paso 2: El proceso 0 envia subconjuntos de x e y
   * ---------------------------------------------------------- */
  if (mi_id == 0) {
    for (i=1; i<numero_procesos; i++) {
      desplazamiento_i = i*promedio_n;
      mis_puntos = (i < numero_procesos -1) ? promedio_n : promedio_n + n_restante;
      MPI_Send (&desplazamiento_i, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
      MPI_Send (&mis_puntos, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
      MPI_Send (&x[desplazamiento_i], mis_puntos, MPI_DOUBLE, i, 3, MPI_COMM_WORLD);
      MPI_Send (&y[desplazamiento_i], mis_puntos, MPI_DOUBLE, i, 4, MPI_COMM_WORLD);
    }
  }
  else {
    /* ---------------los otros procesos reciben---------------- */
    MPI_Recv (&desplazamiento_i, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &estado_i);
    MPI_Recv (&mis_puntos, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &estado_i);
    MPI_Recv (&x[desplazamiento_i], mis_puntos, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD,
	      &estado_i);
    MPI_Recv (&y[desplazamiento_i], mis_puntos, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD,
	      &estado_i);
    printf ("id %d: ", mi_id);
    for (i=0; i<n; i++) printf("%4.2lf ", x[i]);
    printf ("\n");
    /* ---------------------------------------------------------- */
  }

  /* ----------------------------------------------------------
   * Paso 3: Cada proceso calcula su suma parcial
   * ---------------------------------------------------------- */
  miSUMAx = 0; miSUMAy = 0; miSUMAxy = 0; miSUMAxx = 0;
  if (mi_id == 0) {
    desplazamiento_i = 0;
    mis_puntos = promedio_n;
  }
  for (j=0; j<mis_puntos; j++) {
    miSUMAx = miSUMAx + x[desplazamiento_i+j];
    miSUMAy = miSUMAy + y[desplazamiento_i+j];
    miSUMAxy = miSUMAxy + x[desplazamiento_i+j]*y[desplazamiento_i+j];
    miSUMAxx = miSUMAxx + x[desplazamiento_i+j]*x[desplazamiento_i+j];
  }
  
  /* ----------------------------------------------------------
   * Paso 4: El proceso 0 recibe sumas parciales de los otros
   * ---------------------------------------------------------- */
  if (mi_id != 0) {
    MPI_Send (&miSUMAx, 1, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
    MPI_Send (&miSUMAy, 1, MPI_DOUBLE, 0, 6, MPI_COMM_WORLD);
    MPI_Send (&miSUMAxy,1, MPI_DOUBLE, 0, 7, MPI_COMM_WORLD);
    MPI_Send (&miSUMAxx,1, MPI_DOUBLE, 0, 8, MPI_COMM_WORLD);
	    }
  else {
    SUMAx = miSUMAx; SUMAy = miSUMAy;
    SUMAxy = miSUMAxy; SUMAxx = miSUMAxx;
    for (i=1; i<numero_procesos; i++) {
      MPI_Recv (&miSUMAx, 1, MPI_DOUBLE, i, 5, MPI_COMM_WORLD, &estado_i);
      MPI_Recv (&miSUMAy, 1, MPI_DOUBLE, i, 6, MPI_COMM_WORLD, &estado_i);
      MPI_Recv (&miSUMAxy,1, MPI_DOUBLE, i, 7, MPI_COMM_WORLD, &estado_i);
      MPI_Recv (&miSUMAxx,1, MPI_DOUBLE, i, 8, MPI_COMM_WORLD, &estado_i);
      SUMAx = SUMAx + miSUMAx;
      SUMAy = SUMAy + miSUMAy;
      SUMAxy = SUMAxy + miSUMAxy;
      SUMAxx = SUMAxx + miSUMAxx;
    }
  }

  /* ----------------------------------------------------------
   * Paso 5: El proceso 0 hace los pasos finales
   * ---------------------------------------------------------- */
  if (mi_id == 0) {
    pendiente = ( SUMAx*SUMAy - n*SUMAxy ) / ( SUMAx*SUMAx - n*SUMAxx );
    interseccion_y = ( SUMAy - pendiente*SUMAx ) / n;
    /* esta llamada se usa para lograr un formato de salida consistente */
    /*pausa_personalizada (3);*/
    printf ("\n");
    printf ("La ecuacion lineal que mejor se ajusta a los datos dados:\n");
    printf ("       y = %6.2lfx + %6.2lf\n", pendiente, interseccion_y);
    printf ("--------------------------------------------------\n");
    printf ("   Original (x,y)     Y estimado     Residual\n");
    printf ("--------------------------------------------------\n");

    SUMAresidual = 0;
    for (i=0; i<n; i++) {
      y_estimado = pendiente*x[i] + interseccion_y;
      residual = y[i] - y_estimado;
      SUMAresidual = SUMAresidual + residual*residual;
      printf ("   (%6.2lf %6.2lf)      %6.2lf       %6.2lf\n",
	      x[i], y[i], y_estimado, residual);
    }
    printf("--------------------------------------------------\n");
    printf("Suma residual = %6.2lf\n", SUMAresidual);
  }

  /* ----------------------------------------------------------	*/
  MPI_Finalize();
  return 0;
}
