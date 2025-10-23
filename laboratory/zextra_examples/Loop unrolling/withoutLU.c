#include <stdio.h>
#include <time.h>

int main()
{
  int n=10000;
  long sum=0;

  clock_t start=clock();

  for(int i=0;i<n;i++)
  {
    sum+=(long)i;
  }

  clock_t end=clock();
  
  printf("time is %f\n",(double)(end-start)/CLOCKS_PER_SEC);
  printf("sum of numbers from 0 to 100000 is %ld\n",sum);

  return 0;
}
