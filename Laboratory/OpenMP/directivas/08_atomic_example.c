// Este programa utiliza la directiva atomic para asegurar una suma segura entre hilos.
// Archivo: 08_atomic_example.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    int counter = 0;
    #pragma omp parallel for
    for (int i = 0; i < 10000; i++) {
        #pragma omp atomic
        counter++;
    }
printf("Contador final con atomic:  %d\n", counter);
    return 0;
}