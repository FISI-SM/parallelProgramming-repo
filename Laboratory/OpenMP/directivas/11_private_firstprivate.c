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



    int x = 3;
    omp_set_num_threads(4);
    #pragma omp parallel for private(x)
    for ( int i=0;i<20;++i) {
            x += i ; // x inicialmente vale 3
            printf("X=%d \n", x);
    }       
    

    printf("Fuera de la RP %d  \n", x); // x==3


    x = 10;

    omp_set_num_threads(10);
    #pragma omp parallel private(x)
    {
        x += omp_get_thread_num();
        printf("Hilo  %d  tiene x= %d\n", omp_get_thread_num(), x);
    }

    printf("\n x = %d\n",x);

    return 0;
}