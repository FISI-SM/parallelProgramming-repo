// Este programa garantiza el orden de impresión usando la directiva ordered en un bucle paralelo.
/*
 To run:
    $ gcc -fopenmp 13_ordered_example.c -o 13_ordered_example
    $ ./13_ordered_example
 To exec in several threads:
    $ export OMP_NUM_THREADS=4  
*/

#include <stdio.h>
#include <omp.h>

int main() {

    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < 20; ++i) {
        printf("Iteración ordenada  %d  por hilo  %d\n", i, omp_get_thread_num());
    }

    printf("Con ordered\n\n");

    omp_set_num_threads(4);
    #pragma omp parallel for ordered
    for (int i = 0; i < 20; ++i) {
        #pragma omp ordered
            printf("Iteración ordenada  %d  por hilo  %d\n", i, omp_get_thread_num());
    }

    return 0;
}