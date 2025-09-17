/* ----------------------------------------------------------------------

    Este programa prueba el uso de subrutinas de Comunicaciones Colectivas MPI.
    La estructura del programa es:

       --  El nodo maestro consulta por la semilla de numeros aleatorios
       --  La semilla es enviada a todos los nodos (proyecto de laboratorio)
       --  Cada nodo calcula un numero aleatorio basado en la semilla
           y el rango
       --  El nodo con mayor rango calcula el valor medio
           de los numeros aleatorios (proyecto de laboratorio)
       --  Se generan 4 numeros aleatorios mas por cada nodo
       --  El valor maximo y la desviacion estandar de todos
           los numeros aleatorios generados son calculados, y los
           resultados se ponen disponibles para todos los nodos (proyecto de laboratorio)

    Tambien se proporciona una rutina de servicio ObtenerEstadisticas(numeros_aleatorios,N,datos), donde

          numeros_aleatorios:  arreglo de numeros aleatorios (ENTRADA)
          N:     numero de elementos en numeros_aleatorios (ENTRADA)
          datos_salida:  arreglo de tamaño 2 que contiene el valor maximo y
                 desviacion estandar (SALIDA)

  ---------------------------------------------------------------------- */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

void ObtenerEstadisticas(float* numeros_aleatorios, int n, float* valor_resultado);

int main(int argc, char** argv)
{
  int 	        numero_tareas, id_tarea, ii;
  unsigned int  semilla;
  float	        numero_aleatorio[5], suma, valor_medio, numeros[100], valores_resultado[2];
  MPI_Status    estado;
  FILE* archivo;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &id_tarea );
  MPI_Comm_size( MPI_COMM_WORLD, &numero_tareas );
  archivo = fopen( "datos_salida.data", "w" );

  if( id_tarea == 0 )    /*  Obtener semilla de numero aleatorio */
  {
    printf( " Ingrese numero aleatorio como entero positivo\n" );
    scanf( "%u", &semilla);

  }

  /* enviar la semilla desde la raiz a todos los nodos */
  /* esta llamada tiene que estar aqui, no dentro del if (id_tarea == 0), porque esta */
  /* una llamada (MPI_Bcast) es responsable tanto del envio como de la recepcion !    */
  MPI_Bcast(&semilla, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD );

  srand( semilla + id_tarea );

  numero_aleatorio[0] = 100.*(float)rand()/(float)RAND_MAX; /* Obtener un numero aleatorio */

  printf( "\n Tarea %d despues de broadcast; semilla = %u; aleatorio = %8.3f\n",
	 id_tarea, semilla, numero_aleatorio[0] );

/*
   ==============================================================
   Proyecto:  Hacer que el nodo con mayor rango calcule el
             valor medio de los numeros aleatorios y almacene el resultado
             en la variable "valor_medio".
   ==============================================================
*/
  /* primero, necesitamos recopilar todos los valores aleatorios de todos los nodos */
/*  MPI_Gather(&numero_aleatorio[0], 1, MPI_FLOAT, numeros, numero_tareas,
	     MPI_FLOAT,  numero_tareas-1, MPI_COMM_WORLD);
*/
  MPI_Reduce(&numero_aleatorio[0], &suma, 1, MPI_FLOAT, MPI_SUM, numero_tareas-1,
	     MPI_COMM_WORLD);


  if (id_tarea == (numero_tareas-1))
      /* calcular media */
  {
      valor_medio = suma/(float)numero_tareas;

      printf( "\n Tarea %d despues del valor medio; aleatorio[1] =", id_tarea );
      printf( "%8.3f suma = %8.3f media = %8.3f", numero_aleatorio[1], suma, valor_medio );

                               /* La tarea mas alta escribe el valor medio */
      fprintf( archivo, " Para semilla = %d    valor medio = %10.3f\n", semilla, valor_medio );
  }

                                /*  Generar 4 numeros aleatorios mas */
  for( ii=1; ii < 5; ii++ )
    numero_aleatorio[ii] = 100.*(float)rand()/(float)RAND_MAX; 

/*
   ==================================================================
   Proyecto:  Calcular el valor maximo y la desviacion estandar de
             todos los numeros aleatorios generados, y hacer conocidos los resultados
             a todos los nodos.
   Metodo 1:  Usar GATHER seguido de BCAST
   Metodo 2:  Usar ALLGATHER
   ==================================================================
*/
  /*   ------  Metodo 1   ----------- */

  printf( "\n Tarea %d despues del Metodo 1, numero_aleatorio(1:4) =", id_tarea );
  for( ii=1; ii < 5; ii++ )
    printf( " %8.3f", numero_aleatorio[ii] ); 

  /* un truco en Gather es que la raiz especifica el numero de elementos */
  /* POR RECEPCION, no el numero total de elementos esperados! */


  /* recopilar todos los numeros aleatorios primero */
  MPI_Gather(&numero_aleatorio[1], 4, MPI_FLOAT, numeros, 4,
	     MPI_FLOAT,  numero_tareas-1, MPI_COMM_WORLD);
  if( id_tarea == (numero_tareas-1))
  {
      printf( "\n Tarea %d despues del Metodo 1, numeros(0:19) =", id_tarea );
      for( ii=0; ii < numero_tareas*4; ii++ )
	  printf( " %8.3f", numeros[ii] );
      ObtenerEstadisticas(numeros,numero_tareas*4,valores_resultado);
      fprintf( archivo, " (Max, Desv.Est.) = %10.3f%10.3f\n", valores_resultado[0], valores_resultado[1]);
  }
  /* luego transmitir el maximo y la desviacion estandar */
  MPI_Bcast(valores_resultado, 2, MPI_FLOAT, numero_tareas-1, MPI_COMM_WORLD );
  printf( " \n en tarea %d (Max, Desv.Est.) = %10.3f%10.3f\n", id_tarea, valores_resultado[0],
	 valores_resultado[1]);

  /*   ------  Metodo 2   -----------  */

  MPI_Allgather(valores_resultado, 2, MPI_FLOAT, numeros, 2, MPI_FLOAT, MPI_COMM_WORLD);
  printf( "\n Tarea %d despues del Metodo 2, numeros(0:1) =", id_tarea );
  for( ii=0; ii < numero_tareas*2; ii++ )
    printf( " %8.3f", numeros[ii] );
  printf( "\n" );
  if( id_tarea == (numero_tareas-1))
    fprintf( archivo," (Max, Desv.Est.) = %10.3f%10.3f\n", numeros[0], numeros[1]);

  fclose( archivo );
  MPI_Finalize();
  return 0;
}

 
/* ----------------------------------------------------------------------
   Rutina de servicio ObtenerEstadisticas( numeros_aleatorios, N, datos), donde

       numeros_aleatorios:  arreglo de numeros aleatorios (ENTRADA)
       N:     numero de elementos en numeros_aleatorios (ENTRADA)
       datos_salida:  arreglo de tamaño 2 que contiene el valor maximo y
              desviacion estandar (SALIDA)

  ---------------------------------------------------------------------- */

void ObtenerEstadisticas(float* numeros_aleatorios, int N, float* datos_salida)
{
  float  suma, valor_medio, desv_estandar;
  int    ii;

  suma = 0.;
  *datos_salida = 0.;

  for( ii = 0 ; ii < N ; ii++ )
  {
    suma += *(numeros_aleatorios + ii);
    if( *(numeros_aleatorios + ii) > *datos_salida )
      *datos_salida = *(numeros_aleatorios + ii);
  }

  valor_medio = suma/(float)N;
  desv_estandar = 0.;
  for( ii = 0; ii < N; ii++ )
    desv_estandar += (*(numeros_aleatorios + ii) - valor_medio) * (*(numeros_aleatorios + ii) - valor_medio);

  *(datos_salida + 1) = sqrt( desv_estandar/(float)N );
}

