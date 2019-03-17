#include <stdio.h>
#include <stdlib.h>

struct link {
    struct link *next;
    struct link *prev;
    int value; 
} ;


int main(int argc, char **argv) {

    struct link a, b, c;
    a.prev = NULL;
    a.next = NULL;

    b.prev = NULL;
    b.next = NULL;

    c.prev = NULL;
    c.next = NULL;

    a.next = &b;
    b.next = &c;

    b.prev = &a;
    c.prev = &b;

    struct link *p;

    p = &a;

    int count = 0;
    do{
	p->value = count++; 
	printf( "Initial Value pointed at: %d\n",p->value);
	p = p->next;
    } while ( NULL != p); 

    struct link d;
    d.prev = NULL;
    d.next = NULL;	

    d.prev = &a;
    d.next = &b;

    a.next = &d;
    b.prev = &d;

    d.value = 100; 

    p = &a;
    count = 0;
    do {
	printf( "Value pointed at: %d\n",p->value);
	p = p->next;

    } while ( NULL != p);


    printf("Reverse ordered\n");
    p = &c;

    do {
	printf( "Value pointed at: %d\n",p->value);
	p = p->prev;

    } while ( NULL != p);

    return 0;
}

