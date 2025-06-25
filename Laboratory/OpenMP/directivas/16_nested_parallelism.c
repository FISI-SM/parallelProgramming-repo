// Este programa demuestra el uso de paralelismo anidado (nested parallelism).
// Archivo: 16_nested_parallelism.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    omp_set_nested(1);
    #pragma omp parallel num_threads(2)
    {
printf("Nivel 1 hilo  %d\n", omp_get_thread_num());
        #pragma omp parallel num_threads(2)
        {
printf("  Nivel 2 hilo  %d\n", omp_get_thread_num());
        }
    }
    return 0;
}