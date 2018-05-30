#include<stdio.h>
#define SIZE 5

void arrArg(int size,int arr[][5]);

void main(){
	int arr[SIZE][5];
	arrArg(SIZE,arr);
}

void arrArg(int size,int arr[][5]){
	for(int i=0;i<size;i++){
		printf("arr+%d==%p\n",i,arr+i);	//arr: int**
	}
	puts("++++++++++++++++++");
	for(int i=0;i<size*5;i++){
		printf("*arr+%d==%p\n",i,*arr+i);	//*arr: int**
	}
	puts("++++++++++++++++++");
	for(int i=0;i<size*5;i++){
		printf("*(*arr+%d)==%d\n",i,*(*arr+i));	//**arr: int
	}
}
