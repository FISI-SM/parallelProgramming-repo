// Este programa ejecuta una sección de código únicamente por el hilo maestro con la directiva master.
// Archivo: 10_master_example.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    #pragma omp parallel
    {
        #pragma omp master
            printf("Ejecutado solo por el hilo maestro.\n");
            printf("Ejecutado por todos los hilos:  %d\n", omp_get_thread_num());
    }
    return 0;
}