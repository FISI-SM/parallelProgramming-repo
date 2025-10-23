#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ONE_K 1024
#define ONE_M ONE_K * ONE_K
#define ELEM_COUNT 128 * ONE_M

// Define un tipo vectorial de 4 enteros
typedef int v4si __attribute__ ((vector_size (16)));

// Macro para ayudar al acceso a la posición I del vector V de enteros
// del tipo v4si definido arriba
#define VAT(V, I) (V[I >> 2][I & 3])

int main() {

  int n_vets = ELEM_COUNT / 4;
  v4si *a = malloc(n_vets * sizeof(v4si));
  v4si *b = malloc(n_vets * sizeof(v4si));

  for (int i = 0; i < ELEM_COUNT; i++) {
    VAT(a, i) = i;
    VAT(b, i) = i;
  }

  /* Como ahora estamos utilizando operaciones vectoriales, cada una de
   * las operaciones se realiza, en realidad, sobre 4 enteros a la vez.
   * El bucle, por lo tanto, tiene 4 veces menos iteraciones que recorrer
   * (n_vets = ELEM_COUNT / 4).
   */
  // Multiplica todos los elementos
  clock_t start = clock();
  for (int i = 0; i < n_vets; ++i) {
    a[i] *= 7;
    b[i] *= 3;
  }
  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("Multiplicación: %lf\n", elapsedTime);

  // Suma uno a uno
  start = clock();
  for (int i = 0; i < n_vets; ++i) {
    a[i] += b[i];
  }
  elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("Suma: %lf\n", elapsedTime);

  // Imprime el inicio del resultado
  for (int i = 0; i < 10; ++i) {
    printf("a: %d \t b: %d\n", VAT(a, i), VAT(b, i));
  }

  return 0;
}
