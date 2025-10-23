// Este programa usa la directiva single para ejecutar una sección en un único hilo.
/*
 To run:
    $ gcc -fopenmp 14_single_example.c -o 14_single_example
    $ ./14_single_example

 To exec in several threads:
    $ export OMP_NUM_THREADS=4  
*/

#include <stdio.h>
#include <omp.h>

int main() {
    
    #pragma omp parallel
    {
        #pragma omp single
            printf("Este bloque lo ejecuta un solo hilo:  %d\n", omp_get_thread_num());
        printf("Este bloque lo ejecutan todos los hilos:  %d\n", omp_get_thread_num());
    }

    return 0;
}