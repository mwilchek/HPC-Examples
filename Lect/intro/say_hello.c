#include <stdio.h>

void say_hello(char *name); 
int main( void )
{
	char name[] = "Glen";
`
        say_hello(name);
        return 0;
}


void say_hello(char *name){
   printf("Hello, %s\n",name);
}

