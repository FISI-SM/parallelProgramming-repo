#include <stdio.h>
#include <time.h>

int main()
{
  long sum=0;
  clock_t start=clock();

  //loop1
  for(int i=0;i<1000;i++)
  sum+=(long)i;

  //loop2
  for(int i=0;i<1000;i++)
  sum+=(long)i;

  //loop3
  for(int i=0;i<1000;i++)
  sum+=(long)i;
  
  //loop4
  for(int i=0;i<1000;i++)
  sum+=(long)i;

  //loop5
  for(int i=0;i<1000;i++)
  sum+=(long)i;

  //loop6
  for(int i=0;i<1000;i++)
  sum+=(long)i;

  //loop7
  for(int i=0;i<1000;i++)
  sum+=(long)i;
  
  //loop8
  for(int i=0;i<1000;i++)
  sum+=(long)i;

  //loop9
  for(int i=0;i<1000;i++)
  sum+=(long)i;

  //loop10
  for(int i=0;i<1000;i++)
  sum+=(long)i;

  clock_t end=clock();

  printf("time is %f\n",(double)(end-start)/CLOCKS_PER_SEC);
  printf("sum of numbers from 0 to 100000 is %ld\n",sum);

  return 0;
}
