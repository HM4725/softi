#include<stdio.h>

int hold=0;

long fibonacci(int n){
	int num;
	if(n>=2){
		num=fibonacci(n-1)+hold;
		// num=hold+fibonacci(n-1) why??
		hold=num-hold;
		return num;
	} else{
		return 1;
	}
}

void main(){
	int num;
	printf("Input N of fibonacci:");
	scanf("%d",&num);
	if(num<1){
		puts("Error");
		return;
	}
	printf("result: %ld\n",fibonacci(num));
}
