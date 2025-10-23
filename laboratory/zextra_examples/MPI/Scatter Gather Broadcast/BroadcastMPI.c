#include<stdio.h>
#include<mpi.h>

int main(int argc , char *argv[]){
    
    int rank, size; 
    
    int buf;
    
    MPI_Init(&argc,&argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    MPI_Comm_size(MPI_COMM_WORLD , &size);

    if (rank == 0 ){
        buf = 1000;
    }

    printf("The Process No %d and Buffer value before broadcast : %d\n" , rank , buf);

    /*int MPI_Bcast(void *data_to_be_sent, int send_count, MPI_Datatype send_type, 
      int broadcasting_process_ID, MPI_Comm comm);*/

    MPI_Bcast(&buf , 1 , MPI_INT , 0 , MPI_COMM_WORLD);

    printf("The Process No %d and Buffer value After broadcast : %d\n" , rank , buf);

    MPI_Finalize();

    return 0;
   
}

/*
OUTPUT :
$ mpicc BroadcastMPI.c -o broadcast  
$ mpirun -np 5 ./broadcast         
The Process No 0 and Buffer value before broadcast : 1000
The Process No 1 and Buffer value before broadcast : 22000
The Process No 2 and Buffer value before broadcast : 21894
The Process No 3 and Buffer value before broadcast : 21915
The Process No 4 and Buffer value before broadcast : 22016
The Process No 0 and Buffer value After broadcast : 1000
The Process No 1 and Buffer value After broadcast : 1000
The Process No 2 and Buffer value After broadcast : 1000
The Process No 3 and Buffer value After broadcast : 1000
The Process No 4 and Buffer value After broadcast : 1000
                                                                   
*/