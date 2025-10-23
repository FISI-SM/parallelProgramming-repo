#include <stdio.h>
#include <cuda.h>

__global__ void arth(int a, int b, int *c, int *d, int *e, int *f)
{
  *c = a + b;
  *d = a -b;
  *e = a * b;
  *f = a / b;
}

int main()
{
  int a,b,c,d,e,f;
  int *dev_c,*dev_d,*dev_e,*dev_f;
  
  scanf("%d%d",&a,&b);
  
  cudaMalloc((void**)&dev_c, sizeof(int));
  cudaMalloc((void**)&dev_d, sizeof(int));
  cudaMalloc((void**)&dev_e, sizeof(int));
  cudaMalloc((void**)&dev_f, sizeof(int));
  
  arth<<<1,1>>>(a,b,dev_c,dev_d,dev_e,dev_f);
  
  cudaMemcpy(&c, dev_c, sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(&d, dev_d, sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(&e, dev_e, sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(&f, dev_f, sizeof(int), cudaMemcpyDeviceToHost);
  
  printf("%d+ %dis %d\n", a, b, c);
  printf("%d-%dis %d\n", a, b, d);
  printf("%d* %dis %d\n", a, b, e);
  printf("%d/ %dis %d\n", a, b, f);
  
  cudaFree(dev_c);
  cudaFree(dev_d);
  cudaFree(dev_e);
  cudaFree(dev_f);
  
  return 0;
}
