#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define MAXPROC 4     /* number of participating processes */
#define STOP   -1     /* signal to tell the clients stop   */
#define f(x) ((float)(4.0/(1.0+x*x)))
#define pi ((float)(4.0*atan(1.0)))

main(int argc, char * argv[])
{

  /* This simple program approximates pi by computing pi = integral
   * from 0 to 1 of 4/(1+x*x)dx which is approximated by sum 
   * from k=1 to N of 4 / ((1 + (k-1/2)**2 ).  The only input data 
   * required is N.                                       
   */

  /* Each process is given a chunk of the interval to do. */

  float err, sum, w;
  int i, N;

  /* these variables are needed by setting up MPI */
  int size, rank, type;

  double partSum;
  double bound[MAXPROC][3];      /* first one is the staring, second the */
                                 /* length, the third one is step width  */
  double localBound[3], localSum;
  int start, length;
  MPI_Status status;

  /* Insert call to startup routine that returns the number of tasks and
   * the taskid of the current instance.
   */

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  /*
   * server code
   */

  if (rank == 0)
  {
      /* 
       * Now solicit a new value for N.  When it is 0, then you should depart.
       * This would be a good place to unenroll yourself as well.
       */

      printf ("Enter number of approximation intervals:(0 to exit)\n");
      scanf("%d",&N);
      
      
      while (N > 0) 
      {
	  /* calcualte step width, initialize sum */
	  w = 1.0/(float)N;
	  sum = 0.0;

	  /* figure out the steps for each child */
	  start = 0;
	  length = (int)ceil((double)N/(size-1));
printf("size %d\n",size);
	  for (i = 0; i < size-1; i ++)
	  {
printf("start %d  length %d  width %7.5f \n",start,length,w);
	      bound[i][0] = start;
	      bound[i][1] = length;
	      bound[i][2] = w;
	      start += length;
	      if ((start + length) > N)   
		  /* last length may have to be shorten */
		  length = N - start;
	      /* distribute bound to children */
	      MPI_Send(bound[i],3,MPI_DOUBLE,i+1,type, 
		       MPI_COMM_WORLD);
	  }  /* for */
	  
	  /* now collect results */
	  for (i = 0; i < size-1; i ++)
	  {
	      MPI_Recv(&partSum,1,MPI_DOUBLE,MPI_ANY_SOURCE,
		       type, MPI_COMM_WORLD, &status);
	      sum += partSum;
	  }
	  sum = sum * w;
	  err = sum - pi;
	  printf("sum = %7.5f, err = %10e\n", sum, err);
	  printf ("Enter number of approximation intervals:(0 to exit)\n");
	  scanf("%d",&N);
      }   /* while (N > 0) */

      /* here the server is responsible for telling clients to stop */
      for (i = 0; i < size-1; i ++)
      {
	  bound[i][0] = STOP;  /* a special signal */
	  bound[i][1] = STOP;
	  bound[i][2] = STOP;
	  MPI_Send(bound[i],3,MPI_DOUBLE,i+1,type, 
		   MPI_COMM_WORLD);
      }  /* for */
  }
  else    /* child process */
  {
      /* receive information from server (0) */
      MPI_Recv(localBound,3,MPI_DOUBLE,0,
		       type, MPI_COMM_WORLD, &status);
      while (localBound[0] >= 0)  /* continue calculation */
      {
	  localSum = 0;
	  start = (int)localBound[0];
	  length = (int)localBound[1];
	  w = localBound[2];
	  for (i = start; i < start+length; i++)
	      localSum = localSum + f(((float)i-0.5)*w);
      
	  /* send partial result back to server */
	  MPI_Send(&localSum,1,MPI_DOUBLE,0,
		   type, MPI_COMM_WORLD);
	  /* receive information from server (0) */
	  MPI_Recv(localBound,3,MPI_DOUBLE,0,
		   type, MPI_COMM_WORLD, &status);
      }
  }
  MPI_Finalize();
}
