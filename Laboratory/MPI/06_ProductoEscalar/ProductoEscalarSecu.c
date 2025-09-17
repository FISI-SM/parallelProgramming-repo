#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int tama;

    if (argc < 2) {
        printf("No se ha especificado numero de elementos, por defecto sera 100\n");
        printf("Uso: <ejecutable> <cantidad>\n");
        tama = 100;
    } else {
        tama = atoi(argv[1]);
    }

    // Creación y relleno de los vectores (arreglos dinámicos)
    long *VectorA = (long *)malloc(tama * sizeof(long));
    long *VectorB = (long *)malloc(tama * sizeof(long));

    if (VectorA == NULL || VectorB == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    for (long i = 0; i < tama; ++i) {
        VectorA[i] = i + 1;
        VectorB[i] = (i + 1) * 10;
    }

    // Cálculo de la multiplicación escalar entre vectores
    long total = 0;
    for (long i = 0; i < tama; ++i) {
        total += VectorA[i] * VectorB[i];
    }

    printf("Total = %ld\n", total);

    // Liberar memoria
    free(VectorA);
    free(VectorB);

    return 0;
}
