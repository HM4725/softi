#include<stdio.h> // C
#include<stdlib.h> // C
#include<iostream> // C++

int main(){
	/* C */
	int *pnData = (int*)malloc(sizeof(int)*5);
	printf("%p\n",pnData);	
	free(pnData);

	/* C++ */
	int *pnNewData= new int[5];
	std::cout<<pnNewData<<std::endl;
	delete [] pnNewData;

	return 0;
}	
