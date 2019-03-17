#include <stdio.h>
#include <unistd.h>
#include <omp.h>

void delay(int n)
{
	printf("%d-second delay.\n",n);
	sleep(n);
	return;
}

int main (int argc, char *argv[])
{
	   delay(5);
	   delay(1);


/*
   #pragma omp parallel
	{
	#pragma omp sections
		{
		#pragma omp section
			delay(5);
		#pragma omp section
			delay(1);
		#pragma omp section
			delay(1);
		#pragma omp section
			delay(1);
		}
	}
*/
	return 0;
}

