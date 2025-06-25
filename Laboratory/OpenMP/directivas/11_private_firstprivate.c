// Este programa demuestra el uso de variables private y firstprivate dentro de un bloque paralelo.
// Archivo: 11_private_firstprivate.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    int x = 10;
    #pragma omp parallel private(x) firstprivate(x)
    {
        x += omp_get_thread_num();
        #pragma omp critical
printf("Hilo  %d  tiene x= %d\n", omp_get_thread_num(), x);
    }
    return 0;
}