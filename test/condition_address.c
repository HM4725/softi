#include<stdio.h>

int main(){
	int a=0;
	int b=1;
	int *pa=&a;
	int *pn=NULL;

	puts("a=0;");
	a ? puts("a->true") : puts("a->false");
	puts("b=1;");
	b ? puts("b->true") : puts("b->false");
	puts("pa=&a;");
	pa ? puts("pa->true") : puts("pa->false");
	puts("pn=NULL;");
	pn ? puts("pn->true") : puts("pn->false");

	return 0;
}

/*
condition:
	value
	0-> false, else-> true
	address
	NULL-> false, 0x~~(when there is an address data)-> true
*/
