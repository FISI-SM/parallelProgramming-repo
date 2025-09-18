/******************************************************************************
 * File:       rank_mmap.c
 * Purpose:    Implementar un programa en C que calcula el vector de rangos 
 *             de un arreglo A[] usando procesos hijos creados con fork() y 
 *             memoria compartida mediante mapeo de archivos (mmap).
 *             Cada proceso hijo calcula el rango de un elemento y lo almacena
 *             en el vector compartido R[] mapeado en memoria. 
 *             El proceso padre espera a todos los hijos y luego muestra el resultado.
 *
 * Input:      Ninguno (los valores de A[] se inicializan en el programa).
 *
 * Output:     - Vector A[] inicial.
 *             - Vector R[] resultante con los elementos reubicados según su rango.
 *
 * Compile:    gcc -Wall -o rank_mmap rank_mmap.c
 *
 * Run:        ./rank_mmap
 *
 * Algorithm:
 *    1. Inicializar el vector A[] con valores decrecientes de N-1 a 0.
 *    2. Mostrar el vector A[] en pantalla.
 *    3. Crear un archivo temporal ("mapfile") y mapearlo a memoria compartida 
 *       para almacenar el vector R[].
 *    4. Para cada elemento de A[]:
 *         a. Crear un proceso hijo con fork().
 *         b. El hijo calcula el rango de su elemento llamando a compute_rank().
 *         c. El hijo almacena el elemento en la posición de rango dentro de R[].
 *         d. El hijo termina con exit(0).
 *    5. El proceso padre espera a que todos los hijos finalicen (wait()).
 *    6. El proceso padre muestra el vector R[] final.
 *    7. El proceso padre libera la región de memoria compartida con munmap().
 *
 * Note:       - N y A[] están definidos como variables globales.
 *             - El vector R[] reside en una región de memoria compartida creada
 *               mediante un archivo mapeado en memoria (mmap).
 *             - El cálculo de rangos se realiza de forma paralela mediante procesos.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define N 10

int A[N], *R;

void compute_rank(int elem);

int main() {
    int k, fd;

    // Inicializar vector A[]
    for (k = 0; k < N; k++)
        A[k] = N - k - 1;

    printf("Vector A[]:\n");
    for (k = 0; k < N; k++)
        printf("%d ", A[k]);
    printf("\n");

    // Mapear un archivo a una región de memoria compartida para R[]
    fd = open("mapfile", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    lseek(fd, N * sizeof(int), SEEK_SET);
    write(fd, "", 1);
    R = (int *) mmap(NULL, N * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Cada hijo ejecuta una tarea
    for (k = 0; k < N; k++) {
        if (fork() == 0) {
            compute_rank(A[k]);
            exit(0);
        }
    }

    // Padre espera a que terminen todos los hijos
    for (k = 0; k < N; k++)
        wait(NULL);

    // Padre muestra resultado
    printf("Vector R[]:\n");
    for (k = 0; k < N; k++)
        printf("%d ", R[k]);
    printf("\n");

    // Liberar región de memoria compartida
    munmap(R, N * sizeof(int));

    return 0;
}

void compute_rank(int elem) {
    int i, rank = 0;

    for (i = 0; i < N; i++)
        if (elem > A[i])
            rank++;

    R[rank] = elem;
}
