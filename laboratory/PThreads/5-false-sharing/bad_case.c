
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ITERS 100000000

/* Aunque los hilos no comparten los datos, los campos x e y de la
 * estructura comparten la misma línea de caché. Esto provoca que,
 * cuando los hilos se ejecutan en núcleos separados, uno invalide
 * constantemente la caché del otro, disminuyendo el rendimiento.
 * Este problema se conoce como false sharing.
 */
struct coordenada {
  int x;
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
