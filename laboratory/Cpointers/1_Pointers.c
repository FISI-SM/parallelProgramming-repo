#include <stdio.h>

void manipulate(double *pValue)
{
    printf("2. Value of double in manipulate: %.2f\n", *pValue); // 123.4
    *pValue = 10.0;
    printf("3. Value of double in manipulate: %.2f\n", *pValue); // 10.0
}

int main()
{
    int nValue = 8;

    int *pnValue = &nValue;
    // *pnValue = 6;

    printf("Int value: %d\n", nValue);                          // 8
    printf("Pointer to int address: %p\n", pnValue);            // Dirección de pnValue
    printf("Int value via pointer: %d\n", *pnValue);            // 8

    printf("==================\n");

    double dValue = 123.4;

    printf("1. dValue: %.2f\n", dValue);                         // 123.4
    manipulate(&dValue);
    printf("4. dValue: %.2f\n", dValue);                         // 10.0

    return 0;
}
