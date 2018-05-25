#include<stdio.h>

int main(){
	int a=0;
	int *pa=NULL;

	pa=&a;
	*pa=40;

	printf("a=%d\n",a);
	printf("sizeof(a)=%lu\n",sizeof(a));
	printf("&a=%p\n",&a);
	printf("pa=%p\n",pa);
	printf("sizeof(pa)=%lu\n",sizeof(pa));
	printf("&pa=%p\n",&pa);

	return 0;
}
