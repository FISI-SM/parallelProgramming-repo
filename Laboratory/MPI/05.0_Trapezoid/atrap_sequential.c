#include <stdio.h>

/* Function we're integrating */
double f(double x);

/* Serial function for estimating a definite integral using the trapezoidal rule */
double Trap(double left_endpt, double right_endpt, int trap_count, double base_len);

int main(void) {
    int n = 1024 * 1024;      // Number of trapezoids
    double a = 0.0, b = 300000.0; // Interval endpoints
    double h = (b - a) / n;   // Width of each trapezoid
    double total_int;

    total_int = Trap(a, b, n, h);

    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %.15e\n", a, b, total_int);

    return 0;
}

/*------------------------------------------------------------------
 * Function:     Trap
 * Purpose:      Serial function for estimating a definite integral 
 *               using the trapezoidal rule
 * Input args:   left_endpt, right_endpt, trap_count, base_len
 * Return val:   Estimated integral
 */
double Trap(double left_endpt, double right_endpt, int trap_count, double base_len) {
    double estimate, x;
    int i;

    estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
    for (i = 1; i <= trap_count - 1; i++) {
        x = left_endpt + i * base_len;
        estimate += f(x);
    }
    estimate = estimate * base_len;

    return estimate;
}

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Function to integrate
 */
double f(double x) {
    return x * x;
}
