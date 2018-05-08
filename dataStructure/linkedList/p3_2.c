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

void Delete( ElementType X, List L);
Position Find( ElementType X, List L);
Position FindPrevious( ElementType X, List L);
void DeleteList( List L);

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
				tmp = Find(key2, header);
				Insert(key1, header, tmp);
				break;
			case 'd':
				fscanf(input, "%d", &key1);
				Delete(key1, header);
				break;
			case 'f':
				fscanf(input, "%d", &key1);
				tmp = FindPrevious(key1, header);
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
	DeleteList(header);
	fclose(input);
	return 0;
}
List MakeEmpty(List L){
	L=(List)malloc(sizeof(struct Node));
	L->element=-1;
	L->next=NULL;
	return L;
}

int IsEmpty(List L){
	return L->next==NULL;
}

int IsLast(Position P, List L){
	return P->next==NULL;
}
	
void Insert( ElementType X, List L, Position P){
	if (P==NULL){
		printf("Insertion(%d) Failded : cannot find the location to be inserted\n",X);
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

void Delete( ElementType X, List L){
	Position P;
	P=FindPrevious(X,L);
	if(P==NULL){
		printf("cannot delete the header!\n");
	}
	else {
		if(IsLast(P,L)){
			printf("Deletion failed : element %d is not in the list\n",X);
		}
		else {
			Position tmpcell=P->next;
			P->next=tmpcell->next;
			tmpcell->element=0;
			tmpcell->next=NULL;
			free(tmpcell);
		}
	}
}

Position Find( ElementType X, List L){
	Position itr;
	for(itr=L ; !(itr==NULL || itr->element==X) ; itr=itr->next){}
	return itr;
}

Position FindPrevious( ElementType X, List L){
	if( X==-1 ) { return NULL; }
	else {
		Position itr;
		for(itr=L ; !(itr->next==NULL || itr->next->element==X) ; itr=itr->next){}
		return itr;
	}
}

void DeleteList( List L){
	Position P=L;
	Position tmpcell;
	while(P!=NULL) {
		tmpcell=P->next;
		free(P);
		P=tmpcell;
	}
}
