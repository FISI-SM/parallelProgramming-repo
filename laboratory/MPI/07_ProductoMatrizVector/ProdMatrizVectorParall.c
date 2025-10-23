#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char * argv[]) {

    int rank_sz,
        my_rank;
    long **A, // Matriz a multiplicar
         *x, // Vector que vamos a multiplicar
         *y, // Vector donde almacenamos el resultado
         *miFila, // La fila que almacena localmente un proceso
         *comprueba; // Guarda el resultado final (calculado secuencialmente), su valor
                    // debe ser igual al de 'y'

    double tInicio, // Tiempo en el que comienza la ejecucion
           tFin; // Tiempo en el que acaba la ejecucion

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &rank_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    A = (long **) malloc(rank_sz * sizeof(long *)); // Reservamos tantas filas como procesos haya
    x = (long *) malloc(rank_sz * sizeof(long)); // El vector sera del mismo tamanio que el numero
    // de procesadores

    // Solo el proceso 0 ejecuta el siguiente bloque
    if (my_rank == 0) {
        A[0] = (long *) malloc(rank_sz * rank_sz * sizeof(long));
        for (unsigned int i = 1; i < rank_sz; i++) {
            A[i] = A[i - 1] + rank_sz;
        }
        // Reservamos espacio para el resultado
        y = (long *) malloc(rank_sz * sizeof(long));

        // Rellenamos 'A' y 'x' con valores aleatorios
        srand(time(0));
        printf("La matriz y el vector generados son \n");
        for (unsigned int i = 0; i < rank_sz; i++) {
            for (unsigned int j = 0; j < rank_sz; j++) {
                if (j == 0) printf("[");
                A[i][j] = rand() % 1000;
                printf("%ld", A[i][j]);
                if (j == rank_sz - 1) printf("]");
                else printf("  ");
            }
            x[i] = rand() % 100;
            printf("\t  [%ld]\n", x[i]);
        }
        printf("\n");

        // Reservamos espacio para la comprobacion
        comprueba = (long *) malloc(rank_sz * sizeof(long));
        // Lo calculamos de forma secuencial
        for (unsigned int i = 0; i < rank_sz; i++) {
            comprueba[i] = 0;
            for (unsigned int j = 0; j < rank_sz; j++) {
                comprueba[i] += A[i][j] * x[j];
            }
        }
    } // Termina el trozo de codigo que ejecuta solo 0

    // Reservamos espacio para la fila local de cada proceso
    miFila = (long *) malloc(rank_sz * sizeof(long));

    // Repartimos una fila por cada proceso, es posible hacer la reparticion de esta
    // manera ya que la matriz esta creada como un unico vector.
    MPI_Scatter(A ? A[0] : NULL, // Matriz que vamos a compartir
                rank_sz, // Numero de columnas a compartir
                MPI_LONG, // Tipo de dato a enviar
                miFila, // Vector en el que almacenar los datos
                rank_sz, // Numero de columnas a compartir
                MPI_LONG, // Tipo de dato a recibir
                0, // Proceso raiz que envia los datos
                MPI_COMM_WORLD); // Comunicador utilizado (En este caso, el global)

    // Compartimos el vector entre todas los procesos
    MPI_Bcast(x, // Dato a compartir
              rank_sz, // Numero de elementos que se van a enviar y recibir
              MPI_LONG, // Tipo de dato que se compartira
              0, // Proceso raiz que envia los datos
              MPI_COMM_WORLD); // Comunicador utilizado (En este caso, el global)

    // Hacemos una barrera para asegurar que todas los procesos comiencen la ejecucion
    // a la vez, para tener mejor control del tiempo empleado
    MPI_Barrier(MPI_COMM_WORLD);
    // Inicio de medicion de tiempo
    tInicio = MPI_Wtime();

    long subFinal = 0;
    for (unsigned int i = 0; i < rank_sz; i++) {
        subFinal += miFila[i] * x[i];
    }

    // Otra barrera para asegurar que todas ejecuten el siguiente trozo de codigo lo
    // mas proximamente posible
    MPI_Barrier(MPI_COMM_WORLD);
    // fin de medicion de tiempo
    tFin = MPI_Wtime();

    // Recogemos los datos de la multiplicacion, por cada proceso sera un escalar
    // y se recoge en un vector, Gather se asegura de que la recoleccion se haga
    // en el mismo orden en el que se hace el Scatter, con lo que cada escalar
    // acaba en su posicion correspondiente del vector.
    MPI_Gather(&subFinal, // Dato que envia cada proceso
               1, // Numero de elementos que se envian
               MPI_LONG, // Tipo del dato que se envia
               y, // Vector en el que se recolectan los datos
               1, // Numero de datos que se esperan recibir por cada proceso
               MPI_LONG, // Tipo del dato que se recibira
               0, // proceso que va a recibir los datos
               MPI_COMM_WORLD); // Canal de comunicacion (Comunicador Global)

    // Terminamos la ejecucion de los procesos, despues de esto solo existira
    // el proceso 0
    // Ojo! Esto no significa que los demas procesos no ejecuten el resto
    // de codigo despues de "Finalize", es conveniente asegurarnos con una
    // condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
    MPI_Finalize();

    if (my_rank == 0) {

        unsigned int errores = 0;

        printf("El resultado obtenido y el esperado son:\n");
        for (unsigned int i = 0; i < rank_sz; i++) {
            printf("\t%ld\t|\t%ld\n", y[i], comprueba[i]);
            if (comprueba[i] != y[i])
                errores++;
        }

        free(y);
        free(comprueba);
        free(A[0]);

        if (errores) {
            printf("Hubo %u errores.\n", errores);
        } else {
            printf("No hubo errores\n");
            printf("El tiempo tardado ha sido %lf segundos.\n", tFin - tInicio);
        }
    }
    free(x);
    free(A);
    free(miFila);
}
