#include<stdio.h>
#define ULONG64 unsigned long int
#define RAX 0x01234567babecafe

void main(){
	ULONG64 num=RAX&0xffffffff;
	printf("rax=%#lx\n",RAX);
	printf("rax&32bit=%#lx\n",num);
	printf("sizeof(rax)=%lubits\n",8*sizeof(RAX));
	printf("sizeof(rax&32bit)=%lubits\n",8*sizeof(num));
}

/*
   To switch ULONG64 to ULONG32
   To switch RAX to EAX
 */
