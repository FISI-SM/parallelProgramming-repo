
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ONE_K 1024
#define ONE_M ONE_K * ONE_K
#define ELEM_COUNT 128 * ONE_M

int main() {
  int *a = malloc(ELEM_COUNT * sizeof(int));
  int *b = malloc(ELEM_COUNT * sizeof(int));

  for (int i = 0; i < ELEM_COUNT; i++) {
    a[i] = i;
    b[i] = i;
  }

/*
 * Con las optimizaciones del compilador desactivadas, este no detecta
 * las oportunidades de utilizar operaciones vectoriales en los bucles
 * de abajo. No siempre el compilador es capaz de reconocer que un
 * código es vectorizable. Muchas veces, por lo tanto, es posible
 * mejorar el rendimiento de códigos optimizados utilizando
 * operaciones SIMD del procesador.
 */

  //Multiplica tudo
  clock_t start = clock();
  for (int i = 0; i < ELEM_COUNT; ++i) {
    a[i] *= 7;
    b[i] *= 3;
  }
  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("Multiplicación: %lf\n", elapsedTime);

  //Soma um a um
  start = clock();
  for (int i = 0; i < ELEM_COUNT; ++i) {
    a[i] += b[i];
  }
  elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("Suma: %lf\n", elapsedTime);

  //Imprime inicio do resultado
  for (int i = 0; i < 10; ++i) {
    printf("a: %d \t b: %d\n", a[i], b[i]);
  }

  return 0;
}
