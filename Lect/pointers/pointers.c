#include <stdio.h>
#include <stdlib.h>


int main(void){
	int* a = malloc(sizeof(int));

	*a = 12;

	printf("address of a in memory : %p\n", &a);
	printf("address a points to: %p\n", a);

	free(a);
	return 0;
}
