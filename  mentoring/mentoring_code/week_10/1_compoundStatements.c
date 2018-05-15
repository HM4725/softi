#include<stdio.h>

void nonBlock(){
	int sam,index=0;
	while(index++<10)
	sam=10*index+2;
	printf("sam=%d\n",sam);
}

void block(){
	int sam,index=0;
	while(index++<10){
		sam=10*index+2;
		printf("sam=%d\n",sam);
	}
}

void main(){
	puts("##nonBlockStatement##");
	nonBlock();

	puts("#####BlockStatement##");
	block();
}
