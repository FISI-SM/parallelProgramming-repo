#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<math.h>

int main(int argc , char *argv[]){
    
    int rank, size , root = 0;
    MPI_Status st;

    MPI_Init(&argc , &argv);

    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    MPI_Comm_size(MPI_COMM_WORLD , &size);

    int hour, min , shour , smin, total_time , corrected_hours , corrected_mins;
    // Clock server is at 0.  Server is also called Deamon.

    if(rank == root){

        // Producing Random time here. 
        shour = abs((rand()+5)%24);
        smin = abs((rand()+5)%60);

        printf("\nTime at Deamon : %d:%d\n" , shour , smin);

        // Total time is in minutes format --> For example 2:10 = 2 * 60 min + 10 min= 130 mins
        total_time = shour*60 + smin;

        // Get data from Client

        for (int i = 1 ; i < size ; i++){
            
            MPI_Recv(&hour , 1 , MPI_INT , i , 98 , MPI_COMM_WORLD , &st);
            MPI_Recv(&min , 1 , MPI_INT , i , 99 , MPI_COMM_WORLD , &st);

            // Calculating total time from clients recieved hour and mins
            total_time = total_time + hour*60 + min;
           
        } 
            // Calculate average time out of all.
            total_time = (total_time/3);

            // Now split this total time into hours and minutes. 
            shour = (total_time/60);
            smin = (total_time - shour*60);

            printf("Total Time : %d \nAverage Hour Time : %d , Average Minute Time : %d \n", total_time , shour , smin);


        // Send the average time to all process. 
        for(int i = 1 ; i < size ; i++){
            MPI_Send(&shour , 1 , MPI_INT , i , 96 , MPI_COMM_WORLD);
            MPI_Send(&smin , 1 , MPI_INT , i , 97 , MPI_COMM_WORLD);
        }

            printf("\nTime at Deamon After Correction %d:%d\n" , shour , smin);


    }

    for(int i = 1 ; i < size ; i++){
        
        // For client only
        if ( rank == i ){ 

            // Producing Random Time. 
            hour = abs((rand()*i)%24);
            min = abs((rand()*i)%60);

            printf("Time at Child %d : %d:%d\n" , rank , hour , min);
            
            // Sending client Hours and Minutes to server. 
            MPI_Send(&hour , 1 , MPI_INT , 0 , 98 , MPI_COMM_WORLD);
            MPI_Send(&min , 1 , MPI_INT , 0 , 99 , MPI_COMM_WORLD);

            // Reciving Corrected Average Time. 
            MPI_Recv(&shour , 1 , MPI_INT , 0 , 96 , MPI_COMM_WORLD , &st );
            MPI_Recv(&smin , 1 , MPI_INT , 0 , 97 , MPI_COMM_WORLD , &st);

            // Corrected time will be shour and smins. Subtract original hour and min of client from this to get how much to correct

            // For example : shour = 7, smin = 43, If clients time hour = 8 , min = 30, Then corrected time is shour - hour = 7 - 8 = -1 hour from original, smin - min = 43 - 30 = + 13 mins to original. 
            
            corrected_hours = shour - hour;
            corrected_mins = smin - min;
            
            printf("Time at Child %d. After Correction Changes in Hours %d, Changes in Minutes %d, New Time : %d:%d\n",rank , corrected_hours , corrected_mins , shour , smin);

        }

    }
    
    MPI_Finalize();
    return 0; 
}


/* OUTPUT : 

$mpicc ClockSync.c -o clocksync
$mpirun -np 3 ./clocksync

Time at Deamon : 12:51
Total Time : 463 
Average Hour Time : 7 , Average Minute Time : 43 

Time at Deamon After Correction 7:43
Time at Child 1 : 7:46
Time at Child 1. After Correction Changes in Hours 0, Changes in Minutes -3, New Time : 7:43
Time at Child 2 : 2:32
Time at Child 2. After Correction Changes in Hours 5, Changes in Minutes 11, New Time : 7:43
*/
