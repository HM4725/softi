#include<stdio.h>
#include<stdlib.h>

void main(){
/*	int *list1;
	int list2[5];

	list1[0]=34;
	list2[0]=43;*/	// segfault

	int* list1;
	int list2[5];
	printf("%p\n",list1);	//(nil)

	list1=(int*)malloc(5*sizeof(int));
	list1[0]=35;
	list2[0]=53;

	printf("%d %d\n",list1[0],list2[0]);
	free(list1);
}
