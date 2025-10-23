//============================================================================
// Name        : Pointer.c
// Author      : Herminio Paucar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>

int main()
{

  const int NSTRINGS = 5; //
  char *texts[5] = {"one", "two", "three", "four", "five"};
  char **pTexts = texts;

  pTexts += 3;
  printf("%s\n", *pTexts); // "four"
  pTexts -= 2;
  printf("%s\n", *pTexts); // "two"

  char **pEnd = &texts[NSTRINGS];
  pTexts = &texts[0];

  while (pTexts != pEnd)
  {
    printf("%s\n", *pTexts); // "five"
    pTexts++;
  }

  // Set pTexts back to start.
  pTexts = &texts[0];

  long elements = (long)(pEnd - pTexts);

  printf("%ld\n", elements); // 5

  // Set pTexts back to start.
  pTexts = &texts[0];

  pTexts += NSTRINGS / 2;
  printf("%s\n", *pTexts); // "threee"

  return 0;
}
