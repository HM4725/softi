#include<stdio.h>

void swap(int,int);

int main(){
	int val1=10, val2=20;
	printf("val1=%d\nval2=%d\n",val1,val2);
	swap(val1,val2);
	puts("swap(val1,val2)");
	printf("val1=%d\nval2=%d\n",val1,val2);

	return 0;
}

void swap(int a, int b){
	int temp=a;
	a=b;
	b=temp;
}
