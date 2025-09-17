/*
 ============================================================================
 Name        : SendMessageAllTypes
 Author      : Herminio Paucar
 Version     :
 Copyright   : Your copyright notice
 Description :
 Compile Command:
	$ mpiCC -g -Wall -o SendMessageAllTypes SendMessageAllTypes.c
	$ mpiexec  ./SendMessageAllTypes
	$ mpiexec --oversubscribe -n 6 ./SendMessageAllTypes
 ============================================================================
 */

#include "mpi.h"
#include <stdio.h>
#include <string.h>

const int MAX_STRING = 100;

int main(int argc, char *argv[]){
	MPI_Status estado;

	int comm_sz; // Number of processes 
	int my_rank; // My process rank 
	char smSong[MAX_STRING];
	int myGrade;
	double piValue;
	float dollarValue;
	long long longValue;

	// Iniciaizamos el MPI 
	MPI_Init(NULL, NULL);
	// Calculamos el total de procesadores que vamos a usar
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	// Seleccionamos cada procesador 
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	// Hacemos esto para todos los procesadores diferentes del "0" 
	if (my_rank != 0)
	{
		// Generamos el mensaje para cada procesador 
		switch (my_rank)
		{
		case 1:
			sprintf(smSong, "Adelante San Marcos Glorioso, Adelante tu siempre ...");
			MPI_Send(smSong, strlen(smSong) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			break;
		case 2:
			myGrade = 20;
			MPI_Send(&myGrade, sizeof(myGrade), MPI_INT, 0, 0, MPI_COMM_WORLD);
			break;
		case 3:
			piValue = 3.141516;
			MPI_Send(&piValue, sizeof(piValue), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
			break;
		case 4:
			dollarValue = 3.32f;
			MPI_Send(&dollarValue, sizeof(dollarValue), MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
			break;
		case 5:
			longValue = 9223372036854775807;
			MPI_Send(&longValue, sizeof(longValue), MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
			break;
		}
	}
	else
	{
		// Imprime el mensaje cabecera del proceso "0" y el total de procesos 
		printf("Mensajes recibidos por el proceso_%d \n", my_rank);
		// Metodo que recibe el mensaje, posee los mismos 6 argumentos del metodo send 

		MPI_Recv(smSong, MAX_STRING, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &estado);
		printf("Proc_1 su mensaje es: %s\n", smSong);
		
		MPI_Recv(&myGrade, sizeof(myGrade), MPI_INT, 2, 0, MPI_COMM_WORLD, &estado);
		printf("Proc_2 su mensaje es: %d\n", myGrade);
		
		MPI_Recv(&piValue, sizeof(piValue), MPI_DOUBLE, 3, 0, MPI_COMM_WORLD, &estado);
		printf("Proc_3 su mensaje es: %f\n", piValue);
		
		MPI_Recv(&dollarValue, sizeof(dollarValue), MPI_FLOAT, 4, 0, MPI_COMM_WORLD, &estado);
		printf("Proc_4 su mensaje es: %f\n", dollarValue);
		
		MPI_Recv(&longValue, sizeof(longValue), MPI_LONG_LONG, 5, 0, MPI_COMM_WORLD, &estado);
		printf("Proc_5 su mensaje es: %lld\n", longValue);
	}

	MPI_Finalize();
	return 0;
} // main 
