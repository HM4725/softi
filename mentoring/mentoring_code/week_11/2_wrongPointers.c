#include<stdio.h>

void example1(){
	int *pa;
	// NULL 초기화 필수
	printf("%p\n",pa);
	printf("%d\n",*pa);
//	*pa=10;
}	// segentation Error

void example2(){
	int* pa=100;
	*pa=10;
}	// 100 -> 0x~ : from int to pointer without casting

int main(){
	example1();
	example2();
	return 0;
}
