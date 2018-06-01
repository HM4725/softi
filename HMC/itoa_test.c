#include "itoa.h"
#include <stdio.h>

void main(){
	char Decimal[CIPHER];
	int number;
	printf("Input Number: ");
	scanf("%d",&number);
	printf("String: %s\n",itoa(Decimal,number));
}
