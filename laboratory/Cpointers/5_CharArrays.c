//============================================================================
// Name        : Char.c
// Author      : Herminio Paucar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>

int main()
{
	char texts[] = "helloX "; // "\0"

	printf("%s\n", texts); // "helloX "

	printf("SizeOf array: %lu\n", sizeof(texts));

	for (int i = 0; i < sizeof(texts); i++)
	{
		printf("%d: %d-%c\n", i, (int)texts[i], texts[i]);
	}

	return 0;
}
