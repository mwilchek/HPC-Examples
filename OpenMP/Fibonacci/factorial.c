#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long long fact(long long n);

int main(int argc, char **argv){
  long long n = atoi(argv[1]);

  #pragma omp parallel 
  {
    #pragma omp single
      printf("fact(%lld)=%lld\n",n,fact(n));
  }
  return 0;
}

long long fact(long long n) {
  // returns n term in natural fib sequence.
  // where n starts at 0.
  if ( 0 == n ) return 1;
  if ( 1 == n ) return 1;
  long long a;

#pragma omp task shared(a) firstprivate(n) if (n>15)
{
a=n*fact(n-1);
}
#pragma omp taskwait
return a;
}
