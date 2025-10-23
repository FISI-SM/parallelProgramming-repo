/* Adaptado de
 * https://stackoverflow.com/questions/11227809/why-is-it-faster-to-process-a-sorted-array-than-an-unsorted-array
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  int arraySize = 32768;
  int data[arraySize];

  for (int i = 0; i < arraySize; i++)
    data[i] = rand() % 256;

  /* Los accesos se realizan secuencialmente a un vector con elementos
   * aleatorios. El predictor de saltos no es capaz de determinar si
   * la bifurcación será tomada o no en la mayoría de los casos.
   */

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
