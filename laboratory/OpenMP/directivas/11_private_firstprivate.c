// Este programa demuestra el uso de variables private y firstprivate 
// dentro de un bloque paralelo.
/*
 To run:
    $ gcc -fopenmp 11_private_firstprivate.c -o 11_private_firstprivate
    $ ./11_private_firstprivate
 To exec in several threads:
    $ export OMP_NUM_THREADS=4  
*/

#include <stdio.h>
#include <omp.h>

int main() {

    int x = 10;

    omp_set_num_threads(4);
    #pragma omp parallel private(x)
    {
        int tid = omp_get_thread_num();
        x = tid * 2;
        printf("Thread %d: x = %d\n", tid, x);
    }

    printf("\nOutside parallel: x = %d\n", x);


    int y = 10;

    omp_set_num_threads(10);
    #pragma omp parallel firstprivate(y)
    {
        y += omp_get_thread_num();
        printf("Hilo  %d  tiene y= %d\n", omp_get_thread_num(), y);
    }

    printf("\nOutside parallel: y = %d\n", y);

    return 0;
}