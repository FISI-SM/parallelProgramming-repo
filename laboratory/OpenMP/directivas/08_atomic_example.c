// Este programa utiliza la directiva atomic para asegurar una suma segura entre hilos.
/*
 To run:
    $ gcc -fopenmp 08_atomic_example.c -o 08_atomic_example
    $ ./08_atomic_example
 To exec in several threads:
    $ export OMP_NUM_THREADS=4  
*/

#include <stdio.h>
#include <omp.h>

int main() {
    int counter = 0;

    omp_set_num_threads(4);
    //Directiva que distribuye los bucles en los hilos.
    #pragma omp parallel for
        for (int i = 0; i < 21; i++) {
            printf("Yo hilo %d ejecuto el i=%d\n", omp_get_thread_num(), i);
        }
    
    #pragma omp parallel for
    for (int i = 0; i < 1000000; i++) {        
        counter++;
    }
    
    printf("Contador final sin atomic:  %d\n", counter);

    counter = 0;
    #pragma omp parallel for
    for (int i = 0; i < 1000000; i++) {
        #pragma omp atomic
        counter++;
    }
    
    printf("Contador final con atomic:  %d\n", counter);

    return 0;
}