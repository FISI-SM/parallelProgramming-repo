// Este programa usa la directiva single para ejecutar una sección en un único hilo.
// Archivo: 14_single_example.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    #pragma omp parallel
    {
        #pragma omp single
printf("Este bloque lo ejecuta un solo hilo:  %d\n", omp_get_thread_num());
    }
    return 0;
}