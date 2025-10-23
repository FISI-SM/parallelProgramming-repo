//============================================================================
// Name        : Reversing.c
// Author      : Herminio Paucar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>

int main()
{

	char text[] = "Hello there!";

	int nChars = sizeof(text) - 1;

	char *pStart = text;
	char *pEnd = text + nChars - 1;

	// pEnd - pStart > 0
	while (pStart < pEnd)
	{

		char save = *pStart;
		*pStart = *pEnd;
		*pEnd = save;

		pStart++;
		pEnd--;
	}

	printf("%s\n", text);

	return 0;
}
