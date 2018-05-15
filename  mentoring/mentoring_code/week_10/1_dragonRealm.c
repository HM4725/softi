#include<stdio.h>
#include<string.h>
#include<unistd.h>

void main(){
	char str[100];
	scanf("%s",str);

	if(strcmp(str,"hyeonmin")==0){
		printf("cool!\n");
		usleep(1000000);
	}
	printf("%s~ bye!\n",str);
}
