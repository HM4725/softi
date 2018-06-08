#include<stdio.h>

int main(){
	int * pt;
	int (*pa)[3];
	int ar1[2][3];
	int ar2[3][2];
	int **p2;

	pt=&ar1[0][0];
//	pt=&ar1[0];
//	pt=ar1;	
	pa=ar1;
//	pa=ar2;	
	p2=&pt;
	*p2=ar2[0];
//	p2=ar2;	


	return 0;
}
