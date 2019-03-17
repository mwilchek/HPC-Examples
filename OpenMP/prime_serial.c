# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>

int main (){

  int n = 500000;
  int not_primes=0;
  int i,j;
  struct timeval start_time, stop_time, elapsed_time;

gettimeofday(&start_time,NULL);
  for ( i = 2; i <= n; i++ ){
    for ( j = 2; j < i; j++ ){
      if ( i % j == 0 ){
	not_primes++;
	break;
      }
    }
  }
  gettimeofday(&stop_time,NULL);
  timersub(&stop_time, &start_time, &elapsed_time);

  printf("Primes: %d   Time: %f \n", n-not_primes-1, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);

  return 0;
}

