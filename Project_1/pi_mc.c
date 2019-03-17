#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

static long samples = 100000000;

int main (int argc, char *argv[])
{
	if ( argc == 1 ) 
	{
		puts("Usage: ./pi_mc <integer>");
		exit(99);
	}
	long i;  long hits = 0;
	double pi, x, y, test;
	double r = 1.0;   // radius of circle. Side of square is 2*r 
	srand(atoi(argv[1])* (unsigned)time(NULL));


	for(i=0;i<samples; i++)
	{
		x = ( (double)rand())/( (double)RAND_MAX);
		y = ( (double)rand())/( (double)RAND_MAX);

		test = x*x + y*y;

		if (test <= r*r) hits++;
	}

	pi = 4.0 * ((double)hits/(double)samples);

	printf("\n %ld trials, pi is %f \n",samples, pi);

	return 0;
}






