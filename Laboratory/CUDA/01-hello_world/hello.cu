#include <stdio.h>
#include <cuda.h>

__global__ void Hello(void) {
   printf("Hello from thread %d!\n", threadIdx.x);
}

int main(int argc, char* argv[]) {
   int thread_count;

   if (argc < 2) {
      fprintf(stderr, "Usage: %s <thread_count>\n", argv[0]);
      return 1;
   }

   thread_count = strtol(argv[1], NULL, 10);  

   Hello<<<1, thread_count>>>();  

   cudaError_t err = cudaGetLastError();  // Verifica errores en el kernel
   if (err != cudaSuccess) {
      fprintf(stderr, "CUDA Error after kernel launch: %s\n", cudaGetErrorString(err));
      return 1;
   }

   cudaDeviceSynchronize();  // Espera a que GPU termine

   err = cudaGetLastError();  // Verifica errores tras la sincronización
   if (err != cudaSuccess) {
      fprintf(stderr, "CUDA Error after synchronization: %s\n", cudaGetErrorString(err));
      return 1;
   }

   return 0;
}
