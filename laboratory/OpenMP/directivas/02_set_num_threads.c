// Este programa muestra cómo fijar el número de hilos manualmente usando omp_set_num_threads.
/*
 To run:
    $ gcc -fopenmp 02_set_num_threads.c -o 02_set_num_threads.c
    $ ./02_set_num_threads.c
 To exec in several threads:
    $ export OMP_NUM_THREADS=4  
*/

#include <stdio.h>
#include <omp.h>
#include <windows.h>


int main() {

    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int n = omp_get_num_threads();
        
        #pragma omp critical
        {
            Sleep(2000);
            printf("Soy el hilo  %d  de  %d\n", id, n);
        }
    }

    printf("Sin region critica\n");

    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int n = omp_get_num_threads();
        
        Sleep(2000);
        printf("Soy el hilo  %d  de  %d\n", id, n);
    }

    return 0;
}