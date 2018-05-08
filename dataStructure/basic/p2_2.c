#include<stdio.h>

void main(){
	char name[30];
	printf("enter your name:\n");
	scanf("%[^\n]s",name);
	printf("your name is %s\n",name);
}
	
