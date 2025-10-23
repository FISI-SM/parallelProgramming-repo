//============================================================================
// Name        : References.c
// Author      : Herminio Paucar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>

void changeSomething(double *value)
{
	*value = 123.4;
}

int main()
{

	int value1 = 8;
	int *pValue2 = &value1;
	*pValue2 = 10;

	printf("Value1: %d\n", value1);
	printf("Value2: %d\n", *pValue2);

	double value = 4.321;
	changeSomething(&value);
	printf("%f\n", value);

	return 0;
}
