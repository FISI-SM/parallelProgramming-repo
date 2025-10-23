/*
 ============================================================================
 Name        : HelloWorldMPI_01.c
 Author      : Herminio Paucar
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World using MPI
 Compile Command:
    $ mpicc -g -Wall -o HelloWorldMPI_03 HelloWorldMPI_03.c
    $ mpiexec  ./HelloWorldMPI_03
    $ mpiexec -n 4 ./HelloWorldMPI_03
    $ mpiexec --oversubscribe -n 10 ./HelloWorldMPI_03    
 ============================================================================
 */

#include "mpi.h"
#include <stdio.h>
#include <unistd.h> // Necesario para la función sleep

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);               // Inicialización del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Número total de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identificador del proceso

    printf("Proceso %d de %d: esperando %d segundos...\n", rank, size, rank);
    fflush(stdout); // Asegurarse de que el printf no quede en el buffer

    sleep(rank); // Espera rank segundos

    printf("Proceso %d ha terminado después de esperar %d segundos.\n", rank, rank);
    fflush(stdout);

    MPI_Finalize(); // Finaliza el entorno MPI

    return 0;
}