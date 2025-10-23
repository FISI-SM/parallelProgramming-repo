//============================================================================
// Name        : Const.c
// Author      : Herminio Paucar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <string.h>

struct Animal
{
	char name[50];
};

void setName(struct Animal *animal, const char *name)
{
	strncpy(animal->name, name, sizeof(animal->name) - 1);
	animal->name[sizeof(animal->name) - 1] = '\0'; // null-terminate
}

void speak(const struct Animal *animal)
{
	printf("My name is: %s\n", animal->name);
	// const void speak() { cout << "My name is: " << name << endl; } // @suppress("No return")
}

int main()
{

	const double PI = 3.141592;
	printf("%f\n", PI);

	struct Animal animal;
	setName(&animal, "Freddy");
	speak(&animal);

	int value = 8;

	// const int * const pValue = &value;
	int *pValue = &value;

	printf("%d\n", *pValue); // 8

	int number = 11;
	pValue = &number; // Error with this: int * const pValue = &value;
	*pValue = 12;      // Error with this: const int *pValue = &value;

	printf("%d\n", *pValue);

	return 0;
}
