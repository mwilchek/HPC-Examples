#include <stdio.h>

#define LENGTH 10


int main(void)
{
    int a[LENGTH]={1,2,3,4,5,15,14,13,12,11};
    int i;
   
/*    for(i=0;i < LENGTH; i++)
        {
                printf("a[%d] = %d\n",i,a[i]);
        }
*/
	printf("&a=%p &a[0]=%p &(*a)=%p\n",&a,&a[0],&*(a+1));
 
   return 0;
}

