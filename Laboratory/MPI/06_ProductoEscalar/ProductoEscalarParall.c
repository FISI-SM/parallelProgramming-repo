#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int tama, rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc < 2) {
        if (rank == 0) {
            printf("No se ha especificado numero de elementos, multiplo de la cantidad de entrada, por defecto sera %d\n", size * 100);
            printf("Uso: <ejecutable> <cantidad>\n");
        }
        tama = size * 100;
    } else {
        tama = atoi(argv[1]);
        if (tama < size)
            tama = size;
        else {
            int i = 1, num = size;
            while (tama > num) {
                ++i;
                num = size * i;
            }
            if (tama != num) {
                if (rank == 0)
                    printf("Cantidad cambiada a %d\n", num);
                tama = num;
            }
        }
    }

    // Crear y rellenar los vectores
    long *VectorA = NULL;
    long *VectorB = NULL;
    long *VectorALocal = (long *)malloc((tama / size) * sizeof(long));
    long *VectorBLocal = (long *)malloc((tama / size) * sizeof(long));

    if (rank == 0) {
        VectorA = (long *)malloc(tama * sizeof(long));
        VectorB = (long *)malloc(tama * sizeof(long));
        for (long i = 0; i < tama; ++i) {
            VectorA[i] = i + 1;
            VectorB[i] = (i + 1) * 10;
        }
    }

    // Repartimos los valores del vector A
    MPI_Scatter(VectorA, tama / size, MPI_LONG, VectorALocal, tama / size, MPI_LONG, 0, MPI_COMM_WORLD);

    // Repartimos los valores del vector B
    MPI_Scatter(VectorB, tama / size, MPI_LONG, VectorBLocal, tama / size, MPI_LONG, 0, MPI_COMM_WORLD);

    // Cálculo del producto escalar local
    long producto = 0;
    for (long i = 0; i < tama / size; ++i) {
        producto += VectorALocal[i] * VectorBLocal[i];
    }

    // Reducción para obtener el total
    long total = 0;
    MPI_Reduce(&producto, &total, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        printf("Total = %ld\n", total);

    // Liberar memoria
    if (rank == 0) {
        free(VectorA);
        free(VectorB);
    }
    free(VectorALocal);
    free(VectorBLocal);

    MPI_Finalize();
    return 0;
}
