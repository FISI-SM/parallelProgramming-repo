// Este programa usa una barrera para sincronizar los hilos en un punto determinado.
// Archivo: 09_barrier_example.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
printf("Antes de la barrera, hilo  %d\n", id);

        #pragma omp barrier

printf("Después de la barrera, hilo  %d\n", id);
    }
    return 0;
}