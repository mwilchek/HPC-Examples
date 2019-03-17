#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_POINTS 600

typedef struct { /* struct to hold coordinates for each ordered-pair.double */ int x,y;} points;

int main() {


    points *p = (points*) malloc(NUMBER_OF_POINTS * sizeof(points)); 
    if (p == NULL ) { puts("Cannot Allocate Array of Structs.");exit(1);}

    for (int i =0; i < NUMBER_OF_POINTS; i++)
    {
	p[i].x = i;
	p[i].y = i*i;
    }    


    for (int i =0; i < NUMBER_OF_POINTS; i++)
    {
        printf("x = %d, y  = %d\n",p[i].x,p[i].y );
    }


    free(p);

    int *a =  malloc(NUMBER_OF_POINTS * sizeof(int));
    if (a == NULL ) { puts("Cannot Allocate Array of Points.");exit(1);}

    for (int i =0; i < NUMBER_OF_POINTS; i++)
    {
        a[2*i] = i;
        a[2*i+1] = i*i;
    }

    for (int i =0; i < NUMBER_OF_POINTS; i++)
    {
        printf("x = %d, y  = %d\n",a[2*i],a[2*i+1]);
    }

    free(a);
    return 0;
}
