#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n);

int main(int argc, char **argv){
  int N = atoi(argv[1]); 

  printf("%d %d\n",N,fibonacci(N));


  return 0;
}

int fibonacci(int n) {
  // returns n term in natural fib sequence.
  // where n starts at 0.
  if ( 0 == n ) return 0;
  if ( 1 == n ) return 1;
return fibonacci(n-1)+fibonacci(n-2);
}
