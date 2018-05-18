#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	int num[50];
	srand(time(NULL));

	for(int i=0; i<50; i++){
		num[i]=rand()%500+1;
	}

	int count=0;
	while(count<50){
		printf("%d ",num[count]);
		if(count%10==9) puts("");
		count++;
	}
	count=0;
	while(count<50){
		printf("%p ",num+count);
		if(count%5==4) puts("");
		count++;
	}
	return 0;
}
