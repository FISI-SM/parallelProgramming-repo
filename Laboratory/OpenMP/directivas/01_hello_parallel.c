// Este programa imprime un mensaje desde cada hilo usando la directiva #pragma omp parallel.
// Archivo: 01_hello_parallel.cpp

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