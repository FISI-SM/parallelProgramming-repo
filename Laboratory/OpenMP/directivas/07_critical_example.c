// Este programa usa una región crítica para evitar condiciones de carrera al incrementar un contador.
// Archivo: 07_critical_example.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    int counter = 0;
    #pragma omp parallel for
    for (int i = 0; i < 10000; i++) {
        #pragma omp critical
        counter++;
    }
printf("Contador final con critical:  %d\n", counter);
    return 0;
}