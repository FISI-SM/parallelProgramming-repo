
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

  /* Recorre primero columnas y luego filas.
   * No aprovecha la localidad espacial, ya que accede a memoria
   * de forma dispersa entre filas. Produce muchos fallos de caché.
   */

  clock_t start = clock();
  for (int i = 0; i < ELEM_COUNT; ++i) {
    for (int j = 0; j < ELEM_COUNT; j++) {
      y[i] += a[i][j] * x[j];
    }
  }
  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("Tiempo IJ: %lf\n", elapsedTime);

  return 0;
}
