#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>


#define SIZE 1000000000
int main(void){

struct timeval start_time, stop_time, elapsed_time;
gettimeofday(&start_time, NULL);

{
	long long *a,*b,*c;
	a = malloc(SIZE*sizeof(long long));
	b = malloc(SIZE*sizeof(long long));
	c = malloc(SIZE*sizeof(long long));

	long long i;
	long long sum = 0;
#pragma omp parallel 
	for (i = 0; i < SIZE;i++)
	{
		a[i] = i*1;
		b[i] = i*2;
	}

	for (i = 0; i < SIZE;i++)
	{
		c[i] = a[i]*b[i];
	}

	for (i = 0; i < SIZE;i++)
	{
		sum += c[i];
	}	

	printf("sum = %lld\n",sum);

	free(a);
	free(b);
	free(c);
	
}
gettimeofday(&stop_time, NULL);
timersub(&stop_time, &start_time, &elapsed_time);
printf("Time: %f \n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
 return 0;

}
