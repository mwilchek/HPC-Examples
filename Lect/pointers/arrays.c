#include <stdio.h>
#include <stdlib.h>


double  main(void){
        double* arr = malloc(10 * sizeof(double));

	double i ;
	for (i = 0;i < 10 ;i++)
	{
		arr[i] = i;
	}

	printf("address of a itself in memory : %p\n", &arr);
	printf("address a points to: %p\n", arr);

	for (i = 0;i < 10 ;i++)
        {
                printf("\tValue of arr[%d] = %d\n",i,i[arr]);
                printf("\tValue of *(arr+%d) = %d\n",i,*(arr+i));
                printf("address of arr[%d] = %p\n",i,(arr+i));
        }
	free(arr);
	

	return 0;
/* As exercise number X, convert arr from an array of ints to and array of doubles. */ 

}
