#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* S, int X);
//int Pop(Stack* S);

//void DeleteStack(Stack* S);
//int IsEmpty(Stack *S);
int IsFull(Stack *S);

void main(int argc, char* argv[]){
	FILE* fi=fopen(argv[1],"r");

	Stack* stack;
	char input_str[101];
	int max,i=0,a,b,result;

	fgets(input_str,101,fi);
	max=strlen(input_str);
//	printf("Pushed numbers :");
	stack=CreateStack(max);
	
	
	while(input_str[i]!='#'){

		Push(stack,input_str[i++]-48); // '1'-48==1

//		Pop(S);
	}
//	printf("\nevaluation result : %d\n",result);
	fclose(fi);
//	DeleteStack(stack);
}
Stack* CreateStack(int max){
	Stack* S=NULL;
	S=(Stack*)malloc(sizeof(struct Stack));//free
	S->key=(int*)malloc(sizeof(int)*max);//free
	S->max_stack_size=max;
	S->top=-1;
	return S;
}

void Push(Stack* S, int X){
	if (IsFull(S)){
		printf("error\n");
	}
	else {
		S->key[++S->top]=X;
		printf("%d inserted\n",X);
	}
}
//int Pop(Stack* S);

//void DeleteStack(Stack* S);
//int IsEmpty(Stack *S);
int IsFull(Stack *S){
	return (S->top+1 >= S->max_stack_size) ;
}
