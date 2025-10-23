# include <stdlib.h>
# include <stdio.h>
# include <mpi.h>
# include <time.h>

int main ( intargc, char*argv[] );
int circuit_value ( intn, intbvec[] );
void i4_to_bvec ( inti4, intn, intbvec[] );
void timestamp ( );

int main ( intargc, char*argv[] )
{
  # define N 23

  int bvec[N];
  int i, id, ihi, ihi2, ilo, ilo2, j, n = N, p, solution_num_local, solution_num, value;
  double wtime;
  
  MPI_Init ( &argc, &argv );
  MPI_Comm_rank ( MPI_COMM_WORLD, &id );
  MPI_Comm_size ( MPI_COMM_WORLD, &p );
  
  if( id == 0)
  {
    timestamp ( );
  }
  
  ilo = 0;
  ihi = 1;
  
  for( i = 1; i <= n;i++ )
  {
    ihi = ihi * 2;
  }
  
  if( id == 0)
  {
    printf ( "\n");
    printf ( "  The number of logical variables is N = %d\n",n );
    printf ( "  The number of input vectors to check is %d\n", ihi );
    printf ( "\n");
    printf ( "   # Processor       Index    ---------Input Values------------------------\n");
    printf ( "\n");
  }
  
  ilo2 = ((p -id) * ilo + (id) * ihi) / (p);
  ihi2 = ((p -id -1) * ilo + (id + 1) * ihi) / (p);
  
  printf ( "  Processor %diterates from %d<= I < %d\n", id, ilo2, ihi2 );
  
  solution_num_local = 0;
  
  if( id == 0)
  {
    wtime = MPI_Wtime ( );
  }
  
  for( i = ilo2; i < ihi2; i++ )
  {
    i4_to_bvec ( i, n, bvec);
    value = circuit_value ( n, bvec );
    
    if( value == 1)
    {
      solution_num_local = solution_num_local + 1;
      printf ( "  %2d%8d%10d:  ", solution_num_local, id, i );
      
      for( j = 0; j < n; j++ )
      {
        printf ( " %d", bvec[j] );
      }
      
      printf ( "\n");
    }
  }
  
  MPI_Reduce ( &solution_num_local, &solution_num, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );
  
  if( id == 0)
  {
    wtime = MPI_Wtime ( ) -wtime;
    printf ( "\n");
    printf ( "  Number of solutions found was %d\n", solution_num );
    printf ( "  Elapsed wall clock time (seconds) %f\n", wtime );
  }
  
  MPI_Finalize ( );
  
  if( id == 0)
  {
    timestamp ( );
  }
  
  return0;
  
  # undef N
}

int circuit_value ( intn, intbvec[] )
{
  int value;
  value = (bvec[0]||bvec[1])
          &&(!bvec[1]||!bvec[3])
          &&(bvec[2]||bvec[3])
          &&(!bvec[3]||!bvec[4])
          &&(bvec[4]||!bvec[5])
          &&(bvec[5]||!bvec[6])
          &&(bvec[5]||bvec[6])
          &&(bvec[6]||!bvec[15])
          &&(bvec[7]||!bvec[8])
          &&(!bvec[7]||!bvec[13])
          &&(bvec[8]||bvec[9])
          &&(bvec[8]||!bvec[9])
          &&(!bvec[9]||!bvec[10])
          &&(bvec[9]||bvec[11])
          &&(bvec[10]||bvec[11])
          &&(bvec[12]||bvec[13])
          &&(bvec[13]||!bvec[14])
          &&(bvec[14]||bvec[15])
          &&(bvec[14]||bvec[16])
          &&(bvec[17]||bvec[1])
          &&(bvec[18]||!bvec[0])
          &&(bvec[19]||bvec[1])
          &&(bvec[19]||!bvec[18])
          &&(!bvec[19]||!bvec[9])
          &&(bvec[0]||bvec[17])
          &&(!bvec[1]||bvec[20])
          &&(!bvec[21]||bvec[20])
          &&(!bvec[22]||bvec[20])
          &&(!bvec[21]||!bvec[20])
          &&(bvec[22]||!bvec[20]);
  
  return value;
}

void i4_to_bvec ( inti4, intn, intbvec[] )
{
  int i;
  
  for( i = n -1; 0<= i; i--)
  {     
    bvec[i] = i4 % 2;
    i4 = i4 / 2;
  }
  
  return;
}

void timestamp ( void)
{
  # define TIME_SIZE 40
  
  static chartime_buffer[TIME_SIZE];
  const struct tm *tm;
  time_tnow;
  now = time ( NULL);
  tm = localtime ( &now );
  strftime ( time_buffer, TIME_SIZE, "%d%B %Y %I:%M:%S%p", tm );
  
  printf ( "%s\n", time_buffer );
  return;
  # undef TIME_SIZE
}
