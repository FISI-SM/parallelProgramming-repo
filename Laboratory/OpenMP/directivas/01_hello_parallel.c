/* Este programa imprime un mensaje desde cada hilo usando la directiva #pragma omp parallel.
 To run:
    $ gcc -fopenmp 01_hello_parallel.c -o 01_hello_parallel
    $ ./01_hello_parallel
 To exec in several threads:
    $ export OMP_NUM_THREADS=4  
*/

#include <stdio.h>
#include <omp.h>
int main() {
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("Hola desde el hilo  %d\n", id);
    }
    return 0;
}