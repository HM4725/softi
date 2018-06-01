#include<stdio.h>
#define SIZE 5

void arrArg(int size,int arr[][5]);

void main(){
	int arr[SIZE][5];
	arrArg(SIZE,arr);
}

void arrArg(int size,int arr[][5]){
	for(int i=0;i<size;i++){
		printf("arr+%d==%p\n",i,arr+i);	//arr: int**값 저장
	}
	puts("++++++++++++++++++");
	for(int i=0;i<size*5;i++){
		printf("*arr+%d==%p\n",i,*arr+i);	//*arr: int*값 저장
	}
	puts("++++++++++++++++++");
	for(int i=0;i<size*5;i++){
		printf("*(*arr+%d)==%d\n",i,*(*arr+i));	//**arr: int값 저장
	}
}

/* int arr[][5]을 int** arr로 바꾸면
   expected 'int**' but argument is
   of type 'int (*)[5]'
   컴파일 에러

   [이유] 
   1) int** arr: arr+1시 8칸 jump
   2) int[][5] arr: arr+1시 20칸 jump

   -------------------------------
   매개변수가 int arr[]일 때 
   int*값이 인자로 들어가는 경우 ok!

   [이유]
   1) int* arr: arr+1시 4칸 jump
   2) int arr[]: arr+1시 4칸 jump

   --------------------------------
   [결론]
   int*와 int[]는 호환 가능
   int**와 int[][]는 조금 다름
   pointer와 array는 비슷하지만 다르다
*/
