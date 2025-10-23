/******************************************************************************
 * File:       rank_shm.c
 * Purpose:    Implementar un programa en C que calcula el vector de rangos 
 *             de un arreglo A[] usando procesos hijos creados con fork() y 
 *             memoria compartida (System V Shared Memory).
 *             Cada proceso hijo calcula el rango de un elemento y lo almacena
 *             en el vector compartido R[]. El proceso padre espera a todos 
 *             los hijos y luego muestra el resultado.
 *
 * Input:      Ninguno (los valores de A[] se inicializan en el programa).
 *
 * Output:     - Vector A[] inicial.
 *             - Vector R[] resultante con los elementos reubicados según su rango.
 *
 * Compile:    gcc -Wall -o rank_shm rank_shm.c
 *
 * Run:        ./rank_shm
 *
 * Algorithm:
 *    1. Inicializar el vector A[] con valores decrecientes de N-1 a 0.
 *    2. Mostrar el vector A[] en pantalla.
 *    3. Reservar un segmento de memoria compartida para el vector R[].
 *    4. Para cada elemento de A[]:
 *         a. Crear un proceso hijo con fork().
 *         b. El hijo calcula el rango de su elemento llamando a compute_rank().
 *         c. El hijo almacena el elemento en la posición de rango en R[] 
 *            (memoria compartida).
 *         d. El hijo termina con exit(0).
 *    5. El proceso padre espera a que todos los hijos finalicen (wait()).
 *    6. El proceso padre muestra el vector R[] final.
 *    7. El proceso padre libera y elimina el segmento de memoria compartida.
 *
 * Note:       - N y A[] están definidos como variables globales.
 *             - El vector R[] reside en memoria compartida accesible por todos 
 *               los procesos.
 *             - El cálculo de rangos se realiza de forma paralela mediante procesos.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define N 10

int A[N], *R;

void compute_rank(int elem);

int main() {
    int k, shmid;

    // Inicializar vector A[]
    for (k = 0; k < N; k++)
        A[k] = N - k - 1;

    printf("Vector A[]:\n");
    for (k = 0; k < N; k++)
        printf("%d ", A[k]);
    printf("\n");

    // Reservar y mapear un segmento de memoria compartida para R[]
    shmid = shmget(IPC_PRIVATE, N * sizeof(int), S_IRUSR | S_IWUSR);
    R = (int *) shmat(shmid, NULL, 0);

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

    // Liberar y eliminar el segmento de memoria compartida
    shmdt(R);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

void compute_rank(int elem) {
    int i, rank = 0;

    for (i = 0; i < N; i++)
        if (elem > A[i])
            rank++;

    R[rank] = elem;
}
