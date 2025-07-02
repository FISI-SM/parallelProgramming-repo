#include <stdio.h>
#include <cuda.h>

#define n 5

__global__ void add(int *a, int *b, int *c)
{
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  
  if(i < n) 
  {
    c[i] = a[i] + b[i];
  }
}

int main()
{
  int a[n];
  int b[n];
  int i;
  int c[n]= {0};
  int* dev_a;
  int* dev_b;
  int* dev_c;
  
  cudaMalloc((void**)&dev_c, n * sizeof(int));
  cudaMalloc((void**)&dev_a, n * sizeof(int));
  cudaMalloc((void**)&dev_b, n * sizeof(int));
  
  printf("\narray elements (1st):\n");
  
  for(i=0;i<n;i++)
  {
    scanf("%d",&a[i]);
  }
  
  printf("\narray elements (2nd):\n");
  
  for(i=0;i<n;i++)
  {
    scanf("%d",&b[i]);
  }
  
  cudaMemcpy(dev_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_b, b, n* sizeof(int), cudaMemcpyHostToDevice);
  
  add<<<n,1>>>(dev_a, dev_b, dev_c);
  
  cudaMemcpy(c, dev_c, n* sizeof(int), cudaMemcpyDeviceToHost);
  
  printf("\nsum is\n");
  
  for(i=0;i<n;i++)
  {
    printf("%d\n",c[i]);
  }
  
  cudaFree(dev_c);
  cudaFree(dev_a);
  cudaFree(dev_b);
  cudaDeviceReset();
  
  return 0;
}
