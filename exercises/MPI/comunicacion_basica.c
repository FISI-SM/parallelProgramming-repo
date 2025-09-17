/*
 * Version paralela utilizando llamadas MPI
 * Modificado de la version basica para que los trabajadores envien de vuelta
 * un mensaje al maestro, quien imprime un mensaje
 * para cada trabajador
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char **argv )
{
	char mensaje[20];
	int i, rango, tamaño, etiqueta=99;
	MPI_Status estado;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &tamaño);
	MPI_Comm_rank(MPI_COMM_WORLD, &rango);

	if(rango == 0) {
	   strcpy(mensaje, "Hola, mundo");
	   for (i=1; i<tamaño; i++)
	   MPI_Send(mensaje, 13, MPI_CHAR, i,
               etiqueta, MPI_COMM_WORLD);
           printf("nodo %d : %.13s\n", rango, mensaje);
           for (i=1; i<tamaño; i++) {
           MPI_Recv(&rango, 1, MPI_INT, MPI_ANY_SOURCE, etiqueta,
               MPI_COMM_WORLD, &estado);
           printf("nodo %d : Hola de vuelta\n", rango);
           }
	}
  	else {
	  MPI_Recv(mensaje, 20, MPI_CHAR, 0,
	       etiqueta, MPI_COMM_WORLD, &estado);
          MPI_Send(&rango, 1, MPI_INT, 0, etiqueta,
               MPI_COMM_WORLD);
          }
      	MPI_Finalize();
      	return 0;
}
