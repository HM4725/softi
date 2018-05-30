#include"1_fibonacci.h"

void main(){
	int num;
	printf("Input N of fibonacci:");
	scanf("%d",&num);
	if(num<=0){
		puts("Error");
	} else {
		printf("Result: %ld\n",fibonacci(num));
	}
}
