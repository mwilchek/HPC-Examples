#include <stdio.h>
#include <stdlib.h>

struct link {
    struct link *next;
    char name;
    int value; 
} ;


int main(int argc, char **argv) {

    struct link a, b, c;
    	a.next = NULL;
    	a.name = 'a';

    	b.next = NULL;
    	b.name = 'b';

    	c.next = NULL;
    	c.name = 'c';

    	a.next = &b;
    	b.next = &c;

    struct link *p;

    p = &a;

   ( b.next == NULL) ? printf("NULL") : printf("NOT NULL\n");

    int count = 0;
    do {
	p->value = count++; 
	printf( "%d). Value pointed at: %d %c %p\n",count,p->value,p->name,p->next );
	p = p->next;
    } while ( NULL != p ); 

    struct link d;
    d.next = NULL;	
    d.name = 'd';

    d.next = &b;

    a.next = &d;

    d.value = 100; 

    p = &a;
    count = 0;
    do {
	printf( "Value pointed at: %d %c\n",p->value,p->name);
	p = p->next;

    } while ( NULL != p);


    return 0;
}

