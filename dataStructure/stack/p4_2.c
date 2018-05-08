#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define EMPTYSTACK -1

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* S, int X);
int Pop(Stack* S);

void DeleteStack(Stack* S);
int IsEmpty(Stack *S);
int IsFull(Stack *S);

void main(int argc, char* argv[]){
	FILE* fi=fopen(argv[1],"r");

	Stack* stack;
	char input_str[101];
	int max,i=0,result;
	int tmp1,tmp2;

	fgets(input_str,101,fi);
	max=strlen(input_str);
	stack=CreateStack(max);
	
	printf("Top numbers :");
	
	while(input_str[i]!='#'){
		if(isdigit(input_str[i])){
			Push(stack,input_str[i++]-48); // '1'-48==1
		}
		else if (input_str[i]=='+'){
			tmp1=Pop(stack);
			tmp2=Pop(stack);
			if(tmp1==EMPTYSTACK||tmp2==EMPTYSTACK){
				printf("error!\n");
				break;
			}
			else {
				Push(stack,tmp2+tmp1);
				i++;
			}
		}
		else if (input_str[i]=='-'){
			tmp1=Pop(stack);
			tmp2=Pop(stack);
			if(tmp1==EMPTYSTACK||tmp2==EMPTYSTACK){
				printf("error!\n");
				break;
			}
			else {
				Push(stack,tmp2-tmp1);
				i++;
			}
		}
		else if (input_str[i]=='*'){
			tmp1=Pop(stack);
			tmp2=Pop(stack);
			if(tmp1==EMPTYSTACK||tmp2==EMPTYSTACK){
				printf("error!\n");
				break;
			}
			else {
				Push(stack,tmp2*tmp1);
				i++;
			}
		}
		else if (input_str[i]=='/'){
			tmp1=Pop(stack);
			tmp2=Pop(stack);
			if(tmp1==EMPTYSTACK||tmp2==EMPTYSTACK){
				printf("error!\n");
				break;
			}
			else {
				Push(stack,tmp2/tmp1);
				i++;
			}
		}
		else if (input_str[i]=='%'){
			tmp1=Pop(stack);
			tmp2=Pop(stack);
			if(tmp1==EMPTYSTACK||tmp2==EMPTYSTACK){
				printf("error!\n");
				break;
			}
			else {
				Push(stack,tmp2%tmp1);
				i++;
			}
		}
		else {
			printf("error!\n");
			break;
		}
	}
	result=stack->key[0];
	printf("\nevaluation result : %d\n",result);
	fclose(fi);
	DeleteStack(stack);
}
Stack* CreateStack(int max){
	Stack* S=NULL;
	S=(Stack*)malloc(sizeof(struct Stack));
	S->key=(int*)malloc(sizeof(int)*max);
	S->max_stack_size=max;
	S->top=-1;
	return S;
}

void Push(Stack* S, int X){
	if (IsFull(S)||X<=0){
		printf("error\n");
	}
	else {
		S->key[++S->top]=X;
		printf(" %d",S->key[S->top]);
	}
}
int Pop(Stack* S){
	if(IsEmpty(S)){
		printf("error\n");
		return EMPTYSTACK;
	}
	else {
		return S->key[S->top--];
	}
}

void DeleteStack(Stack* S){
	free(S->key);
	free(S);
}

int IsEmpty(Stack *S){
	return (S->top==EMPTYSTACK);
}
int IsFull(Stack *S){
	return (S->top+1 >= S->max_stack_size) ;
}
