#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>


int main(int argc , char *argv[]){

  int rank , size , round = 1, next, prev , recv , uid;
  MPI_Init(&argc , &argv);

  MPI_Status st;
  
  MPI_Comm_rank(MPI_COMM_WORLD , &rank);
  MPI_Comm_size(MPI_COMM_WORLD , &size);

  uid = abs((rand()*(rank+1))%100);

  printf("I am rank %d havind UID : %d\n" , rank ,uid);

  if(rank == size -1){
    next = 0;
  }
  else{
    next = rank + 1;
  }

  if(rank == 0 ){
    prev = size - 1;
  }

  else{
    prev = rank - 1;
  }

  MPI_Send(&uid , 1 , MPI_INT , next , round , MPI_COMM_WORLD);

  while(1){
    MPI_Recv(&recv , 1 , MPI_INT , prev , MPI_ANY_TAG , MPI_COMM_WORLD , &st);

    if(st.MPI_TAG == 100){
      MPI_Send(&recv , 1 , MPI_INT , next , 100 , MPI_COMM_WORLD);
      
      break;
    }

    else{
      round = st.MPI_TAG;

      printf("Round %d , I am rank %d and I recieved UID : %d\n" , round, rank , recv);

      if(recv == uid){
        printf(" I am rank %d I am the Leader, having UID : %d\n" , rank , uid);

        MPI_Send(&rank , 1 , MPI_INT , next, 100 , MPI_COMM_WORLD);

        break;
      }

      if ( recv > uid ) {
        MPI_Send(&recv , 1 , MPI_INT, next , round +1 , MPI_COMM_WORLD);
      }
    }
  }

MPI_Finalize();
return 0;

}
