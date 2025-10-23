#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define N 1000               // Número de cuerpos
#define STEPS 100            // Número de pasos de tiempo
#define DT 0.01              // Delta de tiempo
#define G 6.67430e-11        // Constante gravitacional
#define NUM_THREADS 4

typedef struct {
    double x, y;
} Vector;

Vector pos[N], vel[N], acc[N];
double mass[N];
pthread_barrier_t barrier;

void compute_forces(int start, int end) {
    for (int i = start; i < end; ++i) {
        acc[i].x = acc[i].y = 0;
        for (int j = 0; j < N; ++j) {
            if (i == j) continue;
            double dx = pos[j].x - pos[i].x;
            double dy = pos[j].y - pos[i].y;
            double dist = sqrt(dx*dx + dy*dy + 1e-10);
            double F = G * mass[j] / (dist * dist);
            acc[i].x += F * dx / dist;
            acc[i].y += F * dy / dist;
        }
    }
}

void update_positions(int start, int end) {
    for (int i = start; i < end; ++i) {
        vel[i].x += acc[i].x * DT;
        vel[i].y += acc[i].y * DT;
        pos[i].x += vel[i].x * DT;
        pos[i].y += vel[i].y * DT;
    }
}

void* thread_func(void* rank) {
    int id = (long)rank;
    int chunk = N / NUM_THREADS;
    int start = id * chunk;
    int end = (id == NUM_THREADS - 1) ? N : start + chunk;

    for (int step = 0; step < STEPS; ++step) {
        compute_forces(start, end);
        pthread_barrier_wait(&barrier);
        update_positions(start, end);
        pthread_barrier_wait(&barrier);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    // Inicializar posiciones, velocidades y masas
    for (int i = 0; i < N; ++i) {
        pos[i].x = rand() % 1000;
        pos[i].y = rand() % 1000;
        vel[i].x = vel[i].y = 0;
        mass[i] = 1e5;
    }

    for (long t = 0; t < NUM_THREADS; ++t)
        pthread_create(&threads[t], NULL, thread_func, (void*)t);
    
    for (int t = 0; t < NUM_THREADS; ++t)
        pthread_join(threads[t], NULL);

    pthread_barrier_destroy(&barrier);
    return 0;
}
