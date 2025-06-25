// Este programa ejecuta diferentes secciones de código en paralelo utilizando la directiva sections.
// Archivo: 05_sections_example.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
printf("Sección A ejecutada por hilo  %d\n", omp_get_thread_num());

        #pragma omp section
printf("Sección B ejecutada por hilo  %d\n", omp_get_thread_num());
    }
    return 0;
}