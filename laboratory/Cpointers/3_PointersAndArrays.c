//============================================================================
// Name        : Pointers.c
// Author      : Herminio Paucar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>

// Loop through an array using a pointer, with array element reference syntax
// Loop through an array by incrementing a pointer
// Loop through an array, stopping by comparing two pointers

int main()
{
  char *texts[] = {"one", "two", "three"};
  char **pTexts = texts; // &texts[0]

  for (int i = 0; i < sizeof(texts) / sizeof(char *); i++)
  {
    printf("%s ", pTexts[i]); // "one", "two", "three"
  }
  printf("\n");

  for (int i = 0; i < sizeof(texts) / sizeof(char *); i++, pTexts++)
  {
    printf("%p ", (void *)pTexts); // 0xabc
    printf("%s ", *pTexts);        // "one"
    printf("\n");
  }

  printf("\n");

  char **pElement = &texts[0];
  char **pEnd = &texts[2];

  while (1)
  {
    printf("%s ", *pElement); // "one"

    if (pElement == pEnd)
    {
      break;
    }

    pElement++;
  }

  return 0;
}
