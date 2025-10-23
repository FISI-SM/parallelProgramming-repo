
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELEM_COUNT 20000

int main() {
  double *x = malloc(sizeof(double) * ELEM_COUNT);
  double *y = malloc(sizeof(double) * ELEM_COUNT);
  double **a = malloc(sizeof(double*) * ELEM_COUNT);
  for (int i = 0; i < ELEM_COUNT; ++i) {
    a[i] = malloc(sizeof(double) * ELEM_COUNT);
  }

/* El uso del recorrido por filas y solo después por columnas no
 * favorece los accesos con localidad espacial. En lugar de acceder
 * a los elementos secuencialmente dentro de una línea de caché,
 * el código a continuación salta de una fila a otra, desperdiciando
 * las posibles ganancias que ofrece la localidad espacial.
 */

  clock_t start = clock();
  for (int j = 0; j < ELEM_COUNT; j++) {
    for (int i = 0; i < ELEM_COUNT; ++i) {
      y[i] += a[i][j] * x[j];
    }
  }
  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("Tiempo JI: %lf\n", elapsedTime);

  return 0;
}
