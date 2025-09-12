/*
 ============================================================================
 Name        : SendMessage
 Author      : Herminio Paucar
 Version     :
 Copyright   : Your copyright notice
 Description : En este código de inicio se puede ver el funcionamiento de las
               funciones de envío y recepción. Lo que hace es que cada proceso
               se envía a sí mismo el mensaje deseado.
 Compile Command:
    $ mpiCC -g -Wall -o SendMessage01 SendMessage01.c
    $ mpiexec  ./SendMessage01
    $ mpiexec --oversubscribe -n 10 ./SendMessage01
 ============================================================================
 */

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, msg_rcv, msg_send;
    MPI_Status estado;

    MPI_Init(&argc, &argv);               // Inicializamos la comunicacion de los procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador

    msg_send = rank;
    // Envia y recibe mensajes
    MPI_Send(&msg_send // referencia al vector de elementos a enviar
             ,
             1 // tamaño del vector a enviar
             ,
             MPI_INT // Tipo de dato que envias
             ,
             rank // pid del proceso destino
             ,
             0 // etiqueta
             ,
             MPI_COMM_WORLD); // Comunicador por el que se manda

    MPI_Recv(&msg_rcv // Referencia al vector donde se almacenara lo recibido
             ,
             1 // tamaño del vector a recibir
             ,
             MPI_INT // Tipo de dato que recibe
             ,
             rank // pid del proceso origen de la que se recibe
             ,
             0 // etiqueta
             ,
             MPI_COMM_WORLD // Comunicador por el que se recibe
             ,
             &estado); // estructura informativa del estado

    printf("Soy el proceso %d y he recibido %d\n", rank, msg_rcv);

    MPI_Finalize();
    return 0;
}
