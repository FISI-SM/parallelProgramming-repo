#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *merge(int *arr1, int arr1_size, int *arr2, intarr2_size)
{
  int i = 0, j = 0, k = 0;
  int *result_array;
  
  result_array = (int *)malloc((arr1_size + arr2_size) * sizeof(int)); 
  
  while(i < arr1_size && j < arr2_size) 
  {
    if(arr1[i] < arr2[j]) 
    {
      result_array[k] = arr1[i];
      i++;
    }
    
    else 
    {
      result_array[k] = arr2[j];
      j++;
    }
    
    k++;
  }
  
  if(i == arr1_size) 
  {
    while(j < arr2_size) 
    {
      result_array[k] = arr2[j];
      j++;
      k++;
    }
  }
  
  else 
  {
    while(i < arr1_size) 
    {
      result_array[k] = arr1[i];
      i++;
      k++;
    }
  }
  
  return result_array;
}

int my_compare (const void * a, const void * b) 
{
  int _a = *(int*)a;
  int _b = *(int*)b;
  
  if(_a < _b) 
    return -1;
  else if(_a == _b) 
    return 0;
  else 
    return 1;
}

int main(int argc, char  *argv[]) 
{
  int numtasks, rank;
  int piece_size,*piece, *piece2, piece2_size;
  int i=0;
  double arr_size;
  int *arr;
  int step = 0; 
  
  MPI_Status status;
  
  clock_t begin, end, begin_sort, end_sort;
  double time_spent, time_sort;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  
  if(rank == 0) 
  {
    printf("Enter number of data to sort: ");
    scanf("%lf", &arr_size);
    srand(time(NULL));
    arr = (int *)malloc(arr_size* sizeof(int));
    
    for(i = 0; i < arr_size; i++) 
    {
      *(arr + i) = rand() % (int)10000;
    }
    
    if((int)arr_size % numtasks != 0) 
    {
      printf("The number of data to sort is not divisible by the number of processes.");
      MPI_Finalize();
      exit(1);
    }
    
    else 
    {
      piece_size = (int)(arr_size / numtasks);
    }
  }
  
  begin = clock();
  
  MPI_Bcast(&piece_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
  piece = (int *)malloc(piece_size * sizeof(int));
  MPI_Scatter(arr, piece_size, MPI_INT, piece, piece_size, MPI_INT, 0, MPI_COMM_WORLD); 

  begin_sort = clock();
  qsort(piece, piece_size, sizeof(int), my_compare); 
  end_sort = clock();
  time_sort += (double)(end_sort -begin_sort) / CLOCKS_PER_SEC;
  
  step = 1;
  
  while(step < numtasks)
  {
    if(rank % (2 * step) == 0)
    {
      if(rank + step < numtasks)
      {
        MPI_Recv(&piece2_size, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD, &status); 
        piece2 = (int *)malloc(piece2_size * sizeof(int));
        
        MPI_Recv(piece2, piece2_size, MPI_INT, rank + step, 0, MPI_COMM_WORLD, &status);
        begin_sort = clock();
        piece = merge(piece, piece_size, piece2, piece2_size); 
        end_sort = clock();
        time_sort += (double)(end_sort -begin_sort) / CLOCKS_PER_SEC;
        piece_size = piece_size + piece2_size; 
      }
    }
    
    else
    {
      int nearest_process = rank -step; 
      
      MPI_Send(&piece_size, 1, MPI_INT, nearest_process, 0, MPI_COMM_WORLD); 
      MPI_Send(piece, piece_size, MPI_INT, nearest_process, 0, MPI_COMM_WORLD); 
      
      break;
    }
    
    step = step * 2;
  }
  
  if(rank == 0)
  {
    end = clock();
    time_spent = (double)(end -begin) / CLOCKS_PER_SEC;
    
    printf("Time spent parallel: %f\n", time_spent);
    printf("Time spent sorting parallel: %f\n", time_sort);
    
    begin = clock();
    qsort(arr, arr_size, sizeof(int), my_compare);
    end = clock();
    time_spent = (double)(end -begin) / CLOCKS_PER_SEC;
   
    printf("Time spent seq: %f\n", time_spent);
    printf("\nSorted Array : ");
    
    for(i = 0; i < piece_size; i++)
    {
      fprintf(stdout, "%d ", piece[i]); 
    }
    
    printf("\n\n");
  }
  
  MPI_Finalize();
  return 0;
}
