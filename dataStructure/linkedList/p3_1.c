#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node{
	ElementType element;
	Position next;
};
List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Insert( ElementType X, List L, Position P);
void PrintList(List L);

int main(int argc, char *argv[]){
	char command;
	int key1, key2;
	FILE* input;
	Position header;
	Position tmp;
	if(argc == 1)
		input = fopen("input.txt", "r");
	else
		input = fopen(argv[1], "r");
	header = MakeEmpty(header);
	while(1) {
		command = fgetc(input);
		if(feof(input)) break;
		switch(command) {
			case 'i':
				fscanf(input, "%d %d", &key1, &key2);
				///tmp = Find(key2, header); hw3
				///Insert(key1, header, tmp); hw3
				Insert(key1,header,header);
				break;
			case 'd':
				fscanf(input, "%d", &key1);
//				Delete(key1, header);
				break;
			case 'f':
				fscanf(input, "%d", &key1);
//				tmp = FindPrevious(key1, header);
				if(IsLast(tmp, header))
					printf("Could not find %d in the list\n", key1);
				else {
					if(tmp->element>0)
						printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
					else
						printf("Key of the previous node of %d is header.\n", key1);
				}
				break;
			case 'p':
				PrintList(header);
				break;
			default:
				break;
		}
	}
//	DeleteList(header);
	fclose(input);
	return 0;
}
List MakeEmpty(List L){
	L=(List)malloc(sizeof(struct Node));
	L->element=-1;
	L->next=NULL;
	return L;
}
	//free 잊지않기
int IsEmpty(List L){
	return L->next==NULL;
}
int IsLast(Position P, List L){
	Position itr;
	for(itr=L; itr->next!=NULL; itr=itr->next){}
	return P==itr;
}
	
void Insert( ElementType X, List L, Position P){	// key2==-1 일 때
	if (P==NULL){
		// error -> HW3
	}
	else {
		Position An=(Position)malloc(sizeof(struct Node));
		An->element=X;
		An->next=P->next;
		P->next=An;		
	}
}
void PrintList(List L){
	for(Position itr=L->next; itr!=NULL; itr=itr->next){
		printf("key:%d\t",itr->element);
	}
	printf("\n");
}
