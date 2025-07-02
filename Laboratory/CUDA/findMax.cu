#include <stdio.h>
#include <cuda.h>

#define n 10

__global__ void add(int*a, int*max)
{
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  
  if(i < n)
  {
    for(i=0;i<n;i++)
    {
      if(a[i]>*max)
        *max=a[i];
    }
  }
}

int main()
{
  int a[n];
  int i;
  int max;
  int* dev_a;
  int* dev_max;
  
  cudaMalloc((void**)&dev_max, sizeof(int));
  cudaMalloc((void**)&dev_a, n * sizeof(int));
  
  printf("\narray elements:\n");
  
  for(i=0;i<n;i++)
  {
    scanf("%d",&a[i]);
  }
  
  max = a[0];
  
  cudaMemcpy(dev_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_max, &max, sizeof(int), cudaMemcpyHostToDevice);
  add<<<1,1>>>(dev_a, dev_max);
  cudaMemcpy(&max, dev_max, sizeof(int), cudaMemcpyDeviceToHost);
  
  printf("\nMax is %d\n",max);
  
  cudaFree(dev_max);
  cudaFree(dev_a);
  cudaDeviceReset();
  
  return 0;
}
