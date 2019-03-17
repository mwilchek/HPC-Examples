#include<stdio.h>
#include <sys/time.h>

int main(void) {
	struct timeval start_time, stop_time, elapsed_time;
	gettimeofday(&start_time,NULL);
/* Do Something */

	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time);
	printf("Elapsed Time: %f \n",elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
	return 0;
}
