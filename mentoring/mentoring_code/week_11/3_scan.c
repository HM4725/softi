#include<stdio.h>
#define NODATA 0

int scanEx( int* operand1, int* operand2);
int main(){
	int num1=NODATA, num2=NODATA;
	scanEx(&num1,&num2);

	if(num1!=NODATA && num2!=NODATA){
		printf("num1=%d, num2=%d\n",num1,num2);
	} else printf("failed!\n");
	
	return 0;
}

int scanEx(int* operand1, int* operand2){
	printf("My scanf called.\n");
	scanf("%d%d",operand1,operand2);
	return 0;
}
