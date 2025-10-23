#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>

int main(int argc , char *argv[]){
    
    int rank, size , root = 0;
    MPI_Status st;

    int total_time, smin, shour, hour , min , corrected_hours , corrected_mins;

    MPI_Init(&argc , &argv);

    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    MPI_Comm_size(MPI_COMM_WORLD , &size);


    if(rank == root){

        // Producing Random time here. 
        shour = abs((rand()+5)%24);
        smin = abs((rand()+5)%60);
        
        printf("\nTime at Deamon : %d:%d\n" , shour , smin);
        
        total_time = shour * 60 + smin;

        for(int i = 1 ; i < size ; i++){
            MPI_Send(&total_time , 1 , MPI_INT , i , 99 , MPI_COMM_WORLD);
            
            MPI_Recv(&total_time , 1 , MPI_INT , i , 98 , MPI_COMM_WORLD, &st);

        }

        total_time = (total_time/3);
        shour = (total_time/60);
        smin = (total_time - shour*60);

        printf("Total Average Time : %d \nAverage Hour Time : %d , Average Minute Time : %d \n", total_time , shour , smin);

         for(int i = 1 ; i < size ; i++){
            MPI_Send(&shour , 1 , MPI_INT , i , 96 , MPI_COMM_WORLD);
            MPI_Send(&smin , 1 , MPI_INT , i , 97 , MPI_COMM_WORLD);
        }
        printf("\nTime at Deamon After Correction %d:%d\n" , shour , smin);

    }

    for(int i = 1 ; i < size ; i++){
        
        // For client only
        if ( rank == i ){ 
            hour = abs((rand()*i)%24);
            min = abs((rand()*i)%60);

            printf("Time at Child %d : %d:%d\n" , rank , hour , min);

            MPI_Recv(&total_time , 1 , MPI_INT , 0 , 99 , MPI_COMM_WORLD, &st);
            
            total_time = total_time + hour * 60 + min;
            
            MPI_Send(&total_time , 1 , MPI_INT , 0 , 98 , MPI_COMM_WORLD);


            MPI_Recv(&shour , 1 , MPI_INT , 0 , 96 , MPI_COMM_WORLD , &st );
            MPI_Recv(&smin , 1 , MPI_INT , 0 , 97 , MPI_COMM_WORLD , &st);

            corrected_hours = shour - hour;
            corrected_mins = smin - min;
            
            printf("Time at Child %d. After Correction Changes in Hours %d, Changes in Minutes %d, New Time : %d:%d\n",rank , corrected_hours , corrected_mins , shour , smin);

        }
    }

    MPI_Finalize();

    return 0;

}

    
        