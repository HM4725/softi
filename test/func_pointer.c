#include<stdio.h>

typedef void (*SAY)(void);

void HELLO(){
	printf("HELLO!\n");
}

void BYE(){
	printf("BYE!\n");
}

void SEEYA(){
	printf("SEEYA!\n");
}

int main(){
	char ch;
	SAY say;
	scanf("%c",&ch);
	switch(ch){
		case 'h':
			say=HELLO;
			break;
		case 'b':
			say=BYE;
			break;
		default :
			say=SEEYA;
			break;
	}
	say();
	return 0;
}
