/* Adaptado de
 * https://stackoverflow.com/questions/11227809/why-is-it-faster-to-process-a-sorted-array-than-an-unsorted-array
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparar(const void *a, const void *b) {
  return (*(int*)a - *(int*)b);
}

int main() {
  srand(time(NULL));
  int arraySize = 32768;
  int data[arraySize];

  for (int i = 0; i < arraySize; i++)
    data[i] = rand() % 256;

  /* Los accesos se realizan secuencialmente a un vector con elementos
   * que, aunque son aleatorios, están ordenados. En este caso, el
   * predictor de saltos acierta si la bifurcación será tomada en la
   * mayoría de los casos.
   */

  qsort(data, arraySize, sizeof(int), comparar);

  clock_t start = clock();
  long long sum = 0;
  for (int i = 0; i < 100000; i++) {
    for (int c = 0; c < arraySize; ++c) {
      if (data[c] >= 128)
        sum += data[c];
    }
  }

  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("Tiempo total: %lf\n", elapsedTime);
  printf("Suma: %lld\n", sum);
}
