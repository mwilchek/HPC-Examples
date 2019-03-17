#include <stdio.h>

void pbv(int x, double y);
void pbr(int *p_x, double *p_y);

int main( void )
{
	int x = -1;
	double y = 3.14159;

	printf("\nBefore calling pbv(), x = %d, y = %g.", x, y);

	pbv(x, y);

	printf("\nAfter calling pbv(), x = %d, y = %g.\n", x, y);
	printf("###\n#\n#\n#\n###\n");
	pbr(&x, &y);

	printf("\nAfter calling pby_ref(), x = %d, y = %g.\n",x, y);
	return 0;
}

void pbv(int a, double b)
{
	a = 0;
	b = 0.;
        printf("\nCalling from pbv(), x = %d, y = %g.", a, b);
}

void pbr(int *a, double *b)
{
	*a = 0;
	*b = 0.;
        printf("\nCalling from pbr(), x = %d, y = %g.", *a, *b);
}
