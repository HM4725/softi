#include<stdio.h>

void main(){
	const double PI=3.14;
	int const DOZEN=12;

//	PI=1.0;
//	DOZEN=13;

	//////////////////

	int a=10;
	const int *pa=&a;
//	*pa=30;	// Error!
	a=30;	// OK!

	int b=20;
	int* const pb=&b;
//	pb=&a;	// Error!
	*pb=30;	// OK!
	// int const * p ???

}
