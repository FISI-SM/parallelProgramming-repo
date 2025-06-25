// Este programa garantiza el orden de impresión usando la directiva ordered en un bucle paralelo.
// Archivo: 13_ordered_example.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    #pragma omp parallel for ordered
    for (int i = 0; i < 10; ++i) {
        #pragma omp ordered
printf("Iteración ordenada  %d  por hilo  %d\n", i, omp_get_thread_num());
    }
    return 0;
}