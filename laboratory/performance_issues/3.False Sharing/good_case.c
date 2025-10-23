
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ITERS 100000000

/* En esta versión optimizada, los hilos no fueron modificados, pero
 * la introducción de un padding en la estructura garantiza que las
 * variables x e y no queden en la misma línea de caché. Por lo tanto,
 * no ocurre la invalidación mutua de estas líneas por parte de cada
 * núcleo del procesador.
 */

struct coordenada {
  int x;
  char RELLENO[64]; // Evita false sharing
  int y;
};

struct coordenada cord;

void *incrementa_x(void* _) {
  int s = 0;
  for (int i = 0; i < ITERS; i++) {
    cord.x++;
    s += cord.x;
  }
  printf("Suma x: %d\n", s);
  return NULL;
}

void *incrementa_y(void* _) {
  for (int i = 0; i < ITERS; i++)
    cord.y++;
  printf("Suma y: %d\n", cord.y);
  return NULL;
}

int main() {
  pthread_t thread1, thread2;
  clock_t start = clock();

  pthread_create(&thread1, NULL, incrementa_x, NULL);
  pthread_create(&thread2, NULL, incrementa_y, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  double elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
  printf("Tiempo: %lf\n", elapsedTime);
  return 0;
}
