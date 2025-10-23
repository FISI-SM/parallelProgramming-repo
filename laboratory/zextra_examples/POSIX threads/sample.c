#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void* func(void* p)
{
  long tid=(long)p;
  printf("From the function, the thread id = %ld\n",tid); //get current thread id
  pthread_exit(NULL);
  return NULL;
}

int main() 
{
  int rc;
  pthread_t thread; // declare thread

  clock_t start=clock();

  rc=pthread_create(&thread, NULL, func, NULL);

  printf("From the main function, the thread id = %d\n",rc); 
  
  pthread_join(thread, NULL); //join with main thread

  clock_t end=clock(); 
  
  printf("time is %f\n",(double)(end-start)/CLOCKS_PER_SEC);

  return 0;
}
