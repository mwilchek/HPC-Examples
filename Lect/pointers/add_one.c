#include <stdio.h>

#define LENGTH 10

void add_one(int *);
int main(void)
{
    int a[LENGTH]={1,2,3,4,5,15,14,13,12,11};
    int i;
  
    add_one(a);
    for(i=0;i < LENGTH; i++)
        {
                printf("a[%d] = %d\n",i,a[i]);
        }

	printf("&a=%p &a[0]=%p &(*a)=%p\n",&a,&a[0],&*a);
 
   return 0;
}

void add_one(int *array){
    int i;
    for(i=0;i < LENGTH; i++)
        {
		++*(array+i);
        }


}
