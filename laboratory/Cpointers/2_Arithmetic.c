#include <stdio.h>

/*
 * +
 * - 
 * *
 * / 
 * +=
 * -=
 * /= 
 * *=
 * % 
 * %=
 * precedence
 */

// Take large numbers of seconds and convert it to hours, minutes, seconds
// Write a for loop that iterates 10,000 times; output a dot (on the same line) every 100 iteration (use mod %)

int main()
{
    double value1 = (double)7 / 2;
    printf("%.2f\n", value1); // 3.5

    int value2 = (int)7.3;
    printf("%d\n", value2); // 7

    int value3 = 8;
    value3 += 1; // value3 = value3 + 1 or value3++;
    printf("%d\n", value3); // 9

    int value4 = 10;
    value4 /= 5; // value4 = value4 / 5
    printf("%d\n", value4); // 2

    int value5 = 13 % 5;
    printf("%d\n", value5); // 3

    double equation = ((5 / 4) % 2) + (2.3 * 6); // Don't do this: 5/4%2+2.3*6;
    // 14.8
    printf("%.2f\n", equation); // 14.80

    return 0;
}
