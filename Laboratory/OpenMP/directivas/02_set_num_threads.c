// Este programa muestra cómo fijar el número de hilos manualmente usando omp_set_num_threads.
// Archivo: 02_set_num_threads.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int n = omp_get_num_threads();
        #pragma omp critical
printf("Soy el hilo  %d  de  %d\n", id, n);
    }
    return 0;
}