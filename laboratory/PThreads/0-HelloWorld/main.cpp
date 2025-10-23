#include <pthread.h>
#include <stdio.h>

void* imprimir_mensaje(void* arg) {
    printf("Hola desde el hilo\n");
    return NULL;
}

int main() {
    pthread_t hilo;
    pthread_create(&hilo, NULL, imprimir_mensaje, NULL);
    pthread_join(hilo, NULL);
    printf("Hilo finalizado\n");
    return 0;
}

