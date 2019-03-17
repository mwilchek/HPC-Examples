#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fibonacci(int n);

int main(int argc, char **argv){
  int n = atoi(argv[1]);

  #pragma omp parallel
  {
    #pragma omp single
      printf("%d %d\n",n,fibonacci(n));
  }
  return 0;
}

int fibonacci(int n) {
  // returns n term in natural fib sequence.
  // where n starts at 0.
  if ( 0 == n ) return 0;
  if ( 1 == n ) return 1;
  int a,b;

#pragma omp task shared(a) firstprivate(n) if (n>30) 
{
a=fibonacci(n-1);
}
#pragma omp task shared(b) firstprivate(n) if (n>30)
{
b=fibonacci(n-2);
}

#pragma omp taskwait
return a+b;
}
