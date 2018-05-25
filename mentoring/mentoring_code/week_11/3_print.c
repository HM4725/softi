#include<stdio.h>

void printEx(int,int);

int main(){
	int num1=10, num2=-3;
	printEx(num1,num2);
	return 0;
}

void printEx(int operand1, int operand2){
	printf("My printf called.\n");
	printf("first: %d, second: %d\n",operand1,operand2);
}
