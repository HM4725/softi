#include<stdio.h>

void fct(int *arr2);

int main(){
	int arr1[]={1,2};
	printf("arr1= %p\n",arr1);
	printf("&arr1=%p\n",&arr1);

	fct(arr1);
	printf("%d \n",arr1[0]);

	return 0;
}

void fct(int* arr2){	//int arr2[] 라면?
	printf("arr2= %p\n",arr2);
	printf("&arr2=%p\n",&arr2);
	printf("%d \n",arr2[0]);
	arr2[0]=3;
}
