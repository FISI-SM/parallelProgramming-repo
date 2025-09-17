#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define MAXPROC 4     /* numero de procesos participantes */
#define PARAR   -1    /* señal para indicar a los clientes que paren */
#define f(x) ((float)(4.0/(1.0+x*x)))
#define pi ((float)(4.0*atan(1.0)))

int main(int argc, char * argv[])
{

  /* Este programa simple aproxima pi calculando pi = integral
   * de 0 a 1 de 4/(1+x*x)dx que es aproximado por la suma
   * de k=1 a N de 4 / ((1 + (k-1/2)**2 ).  El único dato de entrada
   * requerido es N.
   */

  /* A cada proceso se le asigna un fragmento del intervalo para procesar. */

  float error, suma, ancho;
  int i, N;

  /* estas variables son necesarias para configurar MPI */
  int tamaño, rango, tipo;

  double sumaParcial;
  double limite[MAXPROC][3];     /* primero es el inicio, segundo la */
                                 /* longitud, el tercero es el ancho del paso */
  double limitesLocales[3], sumaLocal;
  int inicio, longitud;
  MPI_Status estado;

  /* Insertar llamada a rutina de inicio que devuelve el numero de tareas y
   * el identificador de la instancia actual.
   */

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&tamaño);
  MPI_Comm_rank(MPI_COMM_WORLD,&rango);

  /*
   * codigo del servidor
   */

  if (rango == 0)
  {
      /*
       * Ahora solicitar un nuevo valor para N. Cuando sea 0, debe salir.
       * Este seria un buen lugar para darse de baja tambien.
       */

      printf ("Ingrese numero de intervalos de aproximacion:(0 para salir)\n");
      scanf("%d",&N);


      while (N > 0)
      {
	  /* calcular ancho del paso, inicializar suma */
	  ancho = 1.0/(float)N;
	  suma = 0.0;

	  /* calcular los pasos para cada hijo */
	  inicio = 0;
	  longitud = (int)ceil((double)N/(tamaño-1));
printf("tamaño %d\n",tamaño);
	  for (i = 0; i < tamaño-1; i ++)
	  {
printf("inicio %d  longitud %d  ancho %7.5f \n",inicio,longitud,ancho);
	      limite[i][0] = inicio;
	      limite[i][1] = longitud;
	      limite[i][2] = ancho;
	      inicio += longitud;
	      if ((inicio + longitud) > N)
		  /* la ultima longitud puede tener que acortarse */
		  longitud = N - inicio;
	      /* distribuir limite a los hijos */
	      MPI_Send(limite[i],3,MPI_DOUBLE,i+1,tipo,
		       MPI_COMM_WORLD);
	  }  /* for */

	  /* ahora recopilar resultados */
	  for (i = 0; i < tamaño-1; i ++)
	  {
	      MPI_Recv(&sumaParcial,1,MPI_DOUBLE,MPI_ANY_SOURCE,
		       tipo, MPI_COMM_WORLD, &estado);
	      suma += sumaParcial;
	  }
	  suma = suma * ancho;
	  error = suma - pi;
	  printf("suma = %7.5f, error = %10e\n", suma, error);
	  printf ("Ingrese numero de intervalos de aproximacion:(0 para salir)\n");
	  scanf("%d",&N);
      }   /* while (N > 0) */

      /* aqui el servidor es responsable de decirle a los clientes que paren */
      for (i = 0; i < tamaño-1; i ++)
      {
	  limite[i][0] = PARAR;  /* una señal especial */
	  limite[i][1] = PARAR;
	  limite[i][2] = PARAR;
	  MPI_Send(limite[i],3,MPI_DOUBLE,i+1,tipo,
		   MPI_COMM_WORLD);
      }  /* for */
  }
  else    /* proceso hijo */
  {
      /* recibir informacion del servidor (0) */
      MPI_Recv(limitesLocales,3,MPI_DOUBLE,0,
		       tipo, MPI_COMM_WORLD, &estado);
      while (limitesLocales[0] >= 0)  /* continuar calculo */
      {
	  sumaLocal = 0;
	  inicio = (int)limitesLocales[0];
	  longitud = (int)limitesLocales[1];
	  ancho = limitesLocales[2];
	  for (i = inicio; i < inicio+longitud; i++)
	      sumaLocal = sumaLocal + f(((float)i-0.5)*ancho);

	  /* enviar resultado parcial de vuelta al servidor */
	  MPI_Send(&sumaLocal,1,MPI_DOUBLE,0,
		   tipo, MPI_COMM_WORLD);
	  /* recibir informacion del servidor (0) */
	  MPI_Recv(limitesLocales,3,MPI_DOUBLE,0,
		   tipo, MPI_COMM_WORLD, &estado);
      }
  }
  MPI_Finalize();
  return 0;
}
