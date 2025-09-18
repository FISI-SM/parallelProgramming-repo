/******************************************************************************
 * File:       rank_fork.c
 * Purpose:    Implementar un programa en C que calcula el vector de rangos 
 *             de un arreglo A[] usando procesos hijos creados con fork().
 *             Cada proceso hijo calcula el rango de un elemento y el proceso
 *             padre espera a todos los hijos y muestra el resultado.
 *
 * Input:      Ninguno (los valores de A[] se inicializan en el programa).
 *
 * Output:     - Vector A[] inicial.
 *             - Vector R[] resultante con los elementos reubicados según su rango.
 *
 * Compile:    gcc -Wall -o rank_fork rank_fork.c
 *
 * Run:        ./rank_fork
 *
 * Algorithm:
 *    1. Inicializar el vector A[] con valores decrecientes de N-1 a 0.
 *    2. Mostrar el vector A[] en pantalla.
 *    3. Para cada elemento de A[]:
 *         a. Crear un proceso hijo con fork().
 *         b. El proceso hijo calcula el rango de su elemento mediante 
 *            compute_rank().
 *         c. El proceso hijo almacena el elemento en su posición de rango en R[].
 *         d. El proceso hijo termina con exit(0).
 *    4. El proceso padre espera a que todos los hijos finalicen (wait()).
 *    5. El proceso padre muestra el vector R[] final.
 *
 * Note:       - N, A[] y R[] están definidos como variables globales.
 *             - El cálculo de rangos se realiza de forma paralela mediante procesos.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10

int A[N], R[N];

void compute_rank(int elem);

int main() {
    int k;

    // Inicializar vector A[]
    for (k = 0; k < N; k++)
        A[k] = N - k - 1;

    printf("Vector A[]:\n");
    for (k = 0; k < N; k++)
        printf("%d ", A[k]);
    printf("\n");

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

    return 0;
}

void compute_rank(int elem) {
    int i, rank = 0;

    for (i = 0; i < N; i++)
        if (elem > A[i])
            rank++;

    R[rank] = elem;
}
