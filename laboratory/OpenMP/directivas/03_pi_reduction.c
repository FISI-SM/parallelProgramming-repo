// Este programa calcula una aproximación de PI utilizando reducción paralela con OpenMP.
/*
 To run:
    $ gcc -fopenmp 03_pi_reduction.c -o 03_pi_reduction
    $ ./03_pi_reduction
 To exec in several threads:
    $ export OMP_NUM_THREADS=4  
*/

#include <stdio.h>
#include <omp.h>

int main() {
    long num_steps = 100000000;
    double step = 1.0 / (double)num_steps;
    double pi = 0.0;

    omp_set_num_threads(4);
    #pragma omp parallel for reduction(+:pi)
    for (long i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        pi += 4.0 / (1.0 + x * x);
    }

    pi *= step;
    
    printf("Valor aproximado de PI:  %f\n", pi);
    return 0;
}