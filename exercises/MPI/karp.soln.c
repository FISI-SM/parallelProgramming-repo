/* karp.soln.c
 * This simple program approximates pi by computing pi = integral
 * from 0 to 1 of 4/(1+x*x)dx which is approximated by sum 
 * from k=1 to N of 4 / ((1 + (k-1/2)**2 ).  The only input data
 * required is N.
 *
 * MPI parallel version 1 RLF  10/11/95
 * Uses only the 6 basic MPI calls
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define f(x) ((float)(4.0/(1.0+x*x)))
#define pi ((float)(4.0*atan(1.0)))

main(int argc, char **argv) {

float 	err, 
	sum, 
	w,
	x;
int 	i, 
	N, 
	mynum, 
	nprocs,
        tag = 123;
void	solicit();
   MPI_Status status;

/* All instances call startup routine to get their rank (mynum) */
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
   MPI_Comm_rank(MPI_COMM_WORLD, &mynum);

/* Step (1): get a value for N */
solicit (&N,nprocs, mynum);

/* Step (2): check for exit condition. */
if (N <= 0) {
   printf("node %d left\n", mynum);
   exit(0);
   }

/* Step (3): do the computation in N steps
 * Parallel Version: there are "nprocs" processes participating.  Each
 * process should do 1/nprocs of the calculation.  Since we want
 * i = 1..n but mynum = 0, 1, 2..., we start off with mynum+1.
 */
while (N > 0) {
   w = 1.0/(float)N;
   sum = 0.0;
   for (i = mynum+1; i <= N; i+=nprocs)
      sum = sum + f(((float)i-0.5)*w);
   sum = sum * w;
   err = sum - pi;

/* Step (4): print the results  
 * Parallel version: collect partial results and let master instance
 * print it.
 */
   if (mynum==0) {
      printf ("host calculated x = %7.5f\n", sum);
      for (i=1; i<nprocs; i++) {
         MPI_Recv(&x,1,MPI_FLOAT,i,tag,
            MPI_COMM_WORLD,&status);
         printf ("host got x = %7.5f\n", x);
         sum=sum+x;
         }
      err = sum - pi;
      printf ("sum, err = %7.5f, %10e\n", sum, err);
      fflush(stdout);
      }
/* Other processes just send their sum and wait for more input */
   else {
      MPI_Send(&sum,1,MPI_FLOAT,0,tag,
         MPI_COMM_WORLD);
      fflush(stdout);
      }
   /* get a value of N for the next run */
   solicit (&N, nprocs, mynum);
  }
}

void solicit (N, nprocs, mynum)
int *N, nprocs, mynum;
{
/* Get a value for N, the number of intervals in the approximation.
 * (Parallel version: master process reads in N and then
 * sends N to all the other processes)
 * Note: A single broadcast operation could be used instead,
 * but is not one of the six basic calls.
*/
   int i, tag = 123;
   MPI_Status status;
   
if (mynum == 0) 
{
   printf ("Enter number of approximation intervals:(0 to exit)\n");
   scanf ("%d", N);
   for (i=1; i<nprocs; i++) {
   MPI_Send(N, 1, MPI_INT, i, tag,
       MPI_COMM_WORLD);
   }
}
else
{
   MPI_Recv(N, 1, MPI_INT, 0, tag,
       MPI_COMM_WORLD, &status);
}
}
