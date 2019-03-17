#include<stdio.h>
#include<stdlib.h>


int main(void) {

/* Automatic variables created on the stack */
	int a;
	int b=5;
	
	printf("a = %d\n",a);
	printf("b = %d\n",b);

	printf("&a = %d\n",&a); /* returns nonsense */
	printf("&a = %p\n",&a); /* returns the address of a*/
	
	return 0;
}
