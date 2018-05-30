#include<stdio.h>
#define max1(x,y) x>y ? x : y

int max2(int,int);
int max3(int,int);

void main(){
	int num1=10,num2=20;
	printf("%d\n",num1>num2 ? num1:num2);
	printf("%d\n",max1(num1,num2));
	printf("%d\n",max2(num1,num2));
	printf("%d\n",max3(num1,num2));
}

int max2(int a,int b){
	if(a>b) return a;
	else return b;
}

int max3(int a,int b){
	return a>b ? a:b ;
}
