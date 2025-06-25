// Este programa muestra cómo se distribuyen iteraciones dinámicamente entre los hilos.
// Archivo: 06_schedule_dynamic.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    const int N = 20;
    #pragma omp parallel for schedule(dynamic, 2)
    for (int i = 0; i < N; i++) {
printf("Iteración  %d  por hilo  %d\n", i, omp_get_thread_num());
    }
    return 0;
}