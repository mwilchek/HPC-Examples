#include<stdio.h>
#include<stdlib.h>



int main(void){
int a = 5;
int *p_a;


printf("a before = %d\n",a);
p_a=&a;
*p_a = 10;
printf("a after = %d\n",a);



return 0;
}
