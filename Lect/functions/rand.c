#include <stdio.h>

unsigned long int next = 1;

int rand(void)
{
    next = next * 1103515245+12345;
    return (unsigned int)(next/65536)%32768;
}

void srand(unsigned long int seed)
{
    next = seed;
}

int main(void)
{
    int i;
    srand(1231234512);

    for (i=0;i<10;i++)
	printf("Your random int is: %d\n",rand());

    return 0;
}
