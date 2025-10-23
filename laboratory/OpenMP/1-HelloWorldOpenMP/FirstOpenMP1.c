/*
 ============================================================================
 Name        : FirstOpenMP.c
 Author      : Herminio
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 To run:
 	$ gcc -fopenmp FirstOpenMP1.c -o FirstOpenMP1
 	$ ./FirstOpenMP1
 To exec in several threads:
 	$ export OMP_NUM_THREADS=4	
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int main(int argc, char *argv[]) {

	printf("01 Fuera de la region Paralela ...");

	/* This creates a team of threads; each thread has own copy of variables  */
	#pragma omp parallel
	{		
		int nt = omp_get_num_threads(); //Numero de hilos
		int id = omp_get_thread_num(); //Id del hilo

		printf("\n Hello World from thread number %d de un total %d", id,
				nt);
	}

	printf("\n02 Fuera de la region Paralela ...\n");

	return 0;
}

