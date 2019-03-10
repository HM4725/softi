#include<stdio.h>
#include<stdlib.h>

typedef struct {
//	int it;
	double t;
	char ch;	//struct 크기: 가장 큰 자료형의 크기의 배수로 정렬
	char ch2;
}STRUCT;

int main(){
	int* pi=malloc(18);
	printf("%lu ",sizeof(*pi));	// ==sizeof(pi[0])
/*	for(int i=0; i<=4;i++){
		pi[i]=i+1;
	}
	for(int i=0; i<=4;i++){
		printf("%d\n",pi[i]);
	}*/
	pi[4]=0xffffffff;	//memory overflow
//	printf("/%p,%p/ ",&pi[3],&pi[4]);//

/*	STRUCT* pst=malloc(20);
	printf("%lu\n",sizeof(*pst));	// ==sizeof(pst[0]);
	for(int i=0; i<20/sizeof(*pst) ; i++){
		pst[i].it=i;
		pst[i].ch='t';
	}
	for(int i=0; i<20/sizeof(*pst) ; i++){
		printf("i=%d, ch=%c\n",pst[i].it,pst[i].ch);
//		printf("ch=%c\n",pst[i].ch);
	}*/
	int* pi1=malloc(20);pi1[0]=3;
	int* pi2=malloc(20);pi2[0]=3;
	int* pi3=malloc(20);pi3[0]=3;
	int* pi4=malloc(20);pi4[0]=3;
	int* pi5=malloc(20);pi5[0]=3;
	int* pi6=malloc(20);pi6[0]=3;
	int* pi7=malloc(20);pi7[0]=3;
	int* pi8=malloc(20);pi8[0]=3;
	int* pi9=malloc(20);pi9[0]=3;
	free(pi);
	free(pi1);
	free(pi2);
	free(pi3);
	free(pi4);
	free(pi5);
	free(pi6);
	free(pi7);
	free(pi8);
	free(pi9);
//	free(pst);
	return 0;
}

/*
1. memory overflow?
2. pointer type casting?
   */
