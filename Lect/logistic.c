#include <stdio.h>
#include <stdlib.h>

/* Program for creating logistic map data. */

int main(){
	int i,j;
	double r,x,upperBound,lowerBound;
	lowerBound=r=2.5; /* Upper and lower bounds on r */
	upperBound=4.0;
	int steps = 1000000;

	FILE *f; 	/* Open file for writing */
	f=fopen("results.dat","w"); 

	for (j=0 ; j<steps ; j++){ /* r ranges from 2.5 to 4 through 1,000,000 steps. */
		r=(upperBound-lowerBound)*j/steps+lowerBound;
		x=0.00079; 	/* Initialize x*/
		for (i=0 ; i<1000 ; i++){ /* calculate 1000 x's for each value of r. */
			x=r*x*(1-x);

			if(i>=900){  /* keep only the last 100 x's for each value of r and write r,x pairs to file. */
				fprintf(f,"%16.14e %16.14e\n",r,x);
			}

			if ( x < 0 || x > 1 ){ /* Do sanity checking. If x strays outside 0,0 1,0 1,1 0,1 square exit with error */
				fprintf( stderr, "x outside bounds. Force quit on x=%e, i= %u, j=%u\n",x,i,j);
			}


		}
	}

	fclose(f); /* Done with file so clean up. */

	return 0;
}

