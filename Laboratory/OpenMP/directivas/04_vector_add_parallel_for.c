// Este programa realiza la suma de dos vectores en paralelo usando #pragma omp parallel for.
// Archivo: 04_vector_add_parallel_for.cpp

#include <stdio.h>
#include <vector>
#include <omp.h>
int main() {
    const int N = 100000;
    vector<int> a(N, 1), b(N, 2), c(N, 0);

    #pragma omp parallel for
    for (int i = 0; i < N; ++i)
        c[i] = a[i] + b[i];

printf("Suma final:  %d\n", c[N-1]);
    return 0;
}