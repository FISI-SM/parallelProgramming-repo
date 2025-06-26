// Este programa protege una región crítica usando cerrojos explícitos con omp_lock_t.
// Archivo: 15_lock_example.cpp

#include <stdio.h>
#include <omp.h>
int main() {
    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel for
    for (int i = 0; i < 10; ++i) {
        omp_set_lock(&lock);
        printf("Sección protegida por hilo  %d\n", omp_get_thread_num());
        omp_unset_lock(&lock);
    }

    omp_destroy_lock(&lock);
    return 0;
}