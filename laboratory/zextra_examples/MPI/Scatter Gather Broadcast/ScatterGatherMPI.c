#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>


/*What happens actually 

    Globaldata 1 3 5 7 scatters (goes one by one) to diff process.

    change values in local process. 

    Process 0 has 1, doubles into 2.
    Process 1 has 3, doubles into 6.
    Process 2 has 5, doubles into 10.
    Process 3 has 7, doubled into 14. 

    gather all value back to same Globaldata 2 6 10 14

 */


int main(int argc , char *argv[]){
    
    int rank, size;
    int *globaldata = NULL;
    int localdata;


    MPI_Init(&argc , &argv);

    MPI_Comm_rank(MPI_COMM_WORLD , &rank);

    MPI_Comm_size(MPI_COMM_WORLD , &size);

    // We will declare global data in rank 0, ie parent. 

    if (rank == 0){
        globaldata = malloc(size * sizeof(int));

        for(int i = 0 ; i < size ; i++){
            globaldata[i] = 2*i+1;
            //Putting all odd numbers in global data 
        }

        printf("Processor %d had Data in global : " , rank );

        for(int i = 0 ; i < size ; i++){
            printf("%d " , globaldata[i]);
        }
        printf("\n");
    }

    // Now global data has 1 3 5 9 ... ect Lets scatter every data to other process 

    /*int MPI_Scatter(void *send_data, int send_count, MPI_Datatype send_type, 
      void *receive_data, int receive_count, MPI_Datatype receive_type, 
      int sending_process_ID, MPI_Comm comm); */

    MPI_Scatter(globaldata , 1 , MPI_INT , &localdata , 1 , MPI_INT , 0 , MPI_COMM_WORLD);

    printf("The processor %d has localdata : %d \n" , rank , localdata);

    localdata = localdata * 2;

    printf("Processor %d has localdata After doubling : %d\n" , rank , localdata); 

    MPI_Gather(&localdata , 1 , MPI_INT , globaldata , 1 , MPI_INT , 0 , MPI_COMM_WORLD );

    if (rank == 0 ){

        printf("Processor %d had Data in global : " , rank );

        for(int i = 0 ; i < size ; i++){
            printf("%d " , globaldata[i]);
        }
        printf("\n");

    }

MPI_Finalize();
return 0;
}

/*OUTPUT :

$ mpicc ScatterGatherMPI.c -o scattergather  
$ mpirun -np 5 ./scattergather             
Processor 0 had Data in global : 1 3 5 7 9 
The processor 0 has localdata : 1 
Processor 0 has localdata After doubling : 2
The processor 1 has localdata : 3 
Processor 1 has localdata After doubling : 6
The processor 2 has localdata : 5 
Processor 2 has localdata After doubling : 10
The processor 3 has localdata : 7 
Processor 3 has localdata After doubling : 14
The processor 4 has localdata : 9 
Processor 4 has localdata After doubling : 18
Processor 0 had Data in global : 2 6 10 14 18 
                                     
*/
