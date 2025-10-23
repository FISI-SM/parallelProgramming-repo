/*
 ============================================================================
 Name        : HelloWorldMPI_04.c
 Author      : Herminio Paucar
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World using MPI
 Compile Command:
    $ mpicc -g -Wall -o HelloWorldMPI_04 HelloWorldMPI_04.c
    $ mpiexec  ./HelloWorldMPI_04
    $ mpiexec -n 4 ./HelloWorldMPI_04
    $ mpiexec --oversubscribe -n 10 ./HelloWorldMPI_04    
 ============================================================================
 */

#include <mpi.h>
#include <stdio.h>

#define ARRAY_SIZE 5

int main(int argc, char *argv[])
{
    int my_rank, comm_sz;   

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    int data[ARRAY_SIZE] = {0, 1, 2, 3, 4}; // Declaración inicial

    // Cada proceso modifica su copia
    for (int i = 0; i < ARRAY_SIZE; i++)
        data[i] *= my_rank;

    // Imprimir el resultado
    printf("Proceso %d: arreglo modificado = ", my_rank);
    for (int i = 0; i < ARRAY_SIZE; i++)
        printf("%d ", data[i]);
    printf("\n");

    MPI_Finalize();

    return 0;
}


