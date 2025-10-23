#include<stdio.h>
#include<mpi.h>

int main(int argc , char *argv[]){

     // in is for recv data and out1 for sending server 0 data and out2 is for sending server1 data. 

    int rank, size , in , out1 , out2 ;

    MPI_Init(&argc , &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    MPI_Comm_size(MPI_COMM_WORLD , &size);
    
    MPI_Status st;

    /*MPI_Send(void *data_to_send , int no_of_data_elements_to_be_sent , MPI_Datatype datatype_of_sending_data , int Destination_Id , int tag ( Message tag ) , MPI_Comm comm (Communicator))*/

    /* MPI_Recv(void *recieved_Data , int no_of_data_elements_expected, MPI_Datatype datatype_of_recieving_data , int Sending_id , int tag , MPI_Comm comm, MPI_Status *status); */


    if( rank == 0 ){
        // server 1 
        // Decimal to Binary
        // Take all the clients ie is from client 2,3,4...... 
        printf("I am server %d \n" , rank);

        for(int i = 2 ; i < size ; i++){
            MPI_Recv(&in , 1 , MPI_INT , i , MPI_ANY_TAG  , MPI_COMM_WORLD , &st);
        
            // data is present in "in"

            out1 = 0; 

            int counter = 1;

            while(in){
                out1 += counter*(in%2);
                counter = counter * 10;
                in = in/2;
            }

            MPI_Send(&out1 , 1 , MPI_INT , i , 99 , MPI_COMM_WORLD );
        }
    }

    // Server2 converts Decimal to octal
        if( rank == 1 ){
        // server 1 
        // Decimal to Binary
        // Take all the clients ie is from client 2,3,4..... 
        printf("I am server %d \n" , rank);

        for(int i = 2 ; i < size ; i++){
            MPI_Recv(&in , 1 , MPI_INT , i , MPI_ANY_TAG  , MPI_COMM_WORLD , &st);
        
            // data is present in "in"

            out2 = 0; 

            int counter = 1;

            while(in){
                out2 += counter*(in%8);
                counter = counter * 10;
                in = in/8;
            }

            MPI_Send(&out2 , 1 , MPI_INT , i , 99 , MPI_COMM_WORLD );
        }
    }


    for(int i = 2 ; i< size ; i++){
        if (rank == i){
            in = i*2;
            printf("The Processor ID %d\n" , rank);
            printf("Value of in : %d\n" , in);

            MPI_Send(&in , 1 , MPI_INT , 0 , 99 , MPI_COMM_WORLD);
            MPI_Send(&in , 1 , MPI_INT , 1 , 99 , MPI_COMM_WORLD);
            MPI_Recv(&out1 , 1 , MPI_INT , 0 , MPI_ANY_TAG , MPI_COMM_WORLD , &st);
            MPI_Recv(&out2 , 1 , MPI_INT , 1 , MPI_ANY_TAG , MPI_COMM_WORLD , &st);
            
            printf("Processor ID %d Binary Value : %d , Octal value : %d  \n" , rank , out1 , out2);
        }
    }
    MPI_Finalize();
    return 0;

}
    

/*
$ mpicc Chat_Server.c -o chatserver
$ mpirun -np 5 ./chatserver
I am server 0 
I am server 1 
The Processor ID 2
Value of in : 4
The Processor ID 3
Value of in : 6
The Processor ID 4
Value of in : 8
Processor ID 3 Binary Value : 110 , Octal value : 6  
Processor ID 4 Binary Value : 1000 , Octal value : 10  
Processor ID 2 Binary Value : 100 , Octal value : 4  
*/
