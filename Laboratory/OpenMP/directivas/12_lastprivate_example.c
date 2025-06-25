// Este programa ilustra cómo obtener el valor de la última iteración usando lastprivate.
// Archivo: 12_lastprivate_example.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    int last_val = 0;
    #pragma omp parallel for lastprivate(last_val)
    for (int i = 0; i < 10; ++i) {
        last_val = i;
    }
printf("Valor final de last_val:  %d\n", last_val);
    return 0;
}