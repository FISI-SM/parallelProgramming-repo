#include <stdio.h>
#include <omp.h>

#pragma omp declare simd
double f(double x) {
    return (4.0 / (1.0 + x * x));
}

double pi(int n) {
    double sum = 0.0;
    double step = 1.0 / n;
    double x;
    int i;

#pragma omp simd linear(i) private(x) reduction(+:sum)
    for (i = 0; i < n; i++) {
        x = (i + 0.5) * step;
        sum += f(x);
    }

    return sum * step;
}

int main() {
    int n = 1000000000; // Number of intervals
    double result = pi(n);
    printf("Approximation of Pi: %.15f\n", result);
    return 0;
}
