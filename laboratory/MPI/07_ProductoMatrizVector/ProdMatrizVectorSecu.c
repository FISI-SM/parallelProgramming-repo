#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * argv[]) {

	long 	**A, // Matriz a multiplicar
			*x, // Vector que vamos a multiplicar
			*comprueba; // Guarda el resultado final (calculado secuencialmente), su valor

	int n;
	if (argc <= 1) { // si no se pasa por parametro el tamaño de la matriz,
					 //se coge por defecto el numero de procesadores
		printf("Falta el tamanio de la matriz, por defecto cogemos 10\n");
		n = 10;
	} else
		n = atoi(argv[1]);

	A = (long **) malloc(n * sizeof(long *));       //reservamos espacio para las n filas de la matriz.
	x = (long *) malloc(n * sizeof(long));          //reservamos espacio para el vector.

	//Rellena la matriz
	A[0] = (long *) malloc(n * n * sizeof(long));
	for (unsigned int i = 1; i < n; i++) {
		A[i] = A[i - 1] + n;
	}

	// Rellena A y x con valores aleatorios
	srand(time(0));
	printf("La matriz y el vector generados son \n");
	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			if (j == 0)
				printf("[");
			A[i][j] = rand() % 1000;
			printf("%ld", A[i][j]);
			if (j == n - 1)
				printf("]");
			else
				printf("  ");
		}
		x[i] = rand() % 100;
		printf("\t  [%ld]\n", x[i]);
	}
	printf("\n");

	comprueba = (long *) malloc(n * sizeof(long));
	//Calculamos la multiplicacion secuencial para
	//despues comprobar que es correcta la solucion.
	for (unsigned int i = 0; i < n; i++) {
		comprueba[i] = 0;
		for (unsigned int j = 0; j < n; j++) {
			comprueba[i] += A[i][j] * x[j];
		}
	}

	printf("El resultado obtenido y el esperado son:\n");
	for (unsigned int i = 0; i < n; i++) {
		printf("%ld\n", comprueba[i]);
	}

	free(comprueba);
	free(A[0]);

	free(x);
	free(A);

	return 0;
}
