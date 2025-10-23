// Este programa ejecuta una sección de código únicamente por el hilo maestro con la directiva master.
/*
 To run:
    $ gcc -fopenmp 10_master_example.c -o 10_master_example
    $ ./10_master_example
 To exec in several threads:
    $ export OMP_NUM_THREADS=4  
*/

#include <stdio.h>
#include <omp.h>

int main() {

    omp_set_num_threads(4);
    #pragma omp parallel
    {
        
        #pragma omp master
            printf("Ejecutado solo por el hilo maestro. %d\n", omp_get_thread_num());
        printf("Ejecutado por todos los hilos:  %d\n", omp_get_thread_num());
    }
    return 0;
}