// Este programa mide el tiempo de ejecución usando omp_get_wtime.
// Archivo: 17_get_wtime_example.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    double start = omp_get_wtime();

    double sum = 0;
    for (int i = 0; i < 1e7; ++i)
        sum += i;

    double end = omp_get_wtime();
    printf("Tiempo transcurrido:  %d  segundos\n", end - start);
    return 0;
}