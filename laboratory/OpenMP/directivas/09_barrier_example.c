// Este programa usa una barrera para sincronizar los hilos en un punto determinado.
/*
 To run:
    $ gcc -fopenmp 09_barrier_example.c -o 09_barrier_example
    $ ./09_barrier_example
 To exec in several threads:
    $ export OMP_NUM_THREADS=4  
*/

#include <stdio.h>
#include <omp.h>

int main() {

    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("M1, hilo  %d\n", id);
        printf("M2, hilo  %d\n", id);
    }


    printf("\nCon barrera \n");

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("M1, Antes de la barrera, hilo  %d\n", id);

        #pragma omp barrier
        printf("M2, Despues de la barrera, hilo  %d\n", id);
    }

    return 0;
}
