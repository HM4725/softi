#include<stdio.h>
#include<stdlib.h>
#define BEGIN	-1
#define TRUE	1
#define FALSE	0

typedef struct HeapStruct Heap;
typedef int ElementType;

Heap* CreateHeap(int heapSize);
void Insert(Heap *heap, int value);
int Find(Heap *heap, int value);
int DeleteMax(Heap* heap);
void PrintHeap(Heap* heap);

struct HeapStruct {
	int Capacity;
	int Size;
	ElementType *Elements;
};

void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1],"r");
	char cv;
	Heap* maxHeap;
	int heapSize,key;
	while(!feof(fi)){
		fscanf(fi,"%c",&cv);
		switch(cv){
			case 'n':
				fscanf(fi,"%d",&heapSize);
				maxHeap=CreateHeap(heapSize);
				break;
			case 'i':
				fscanf(fi,"%d",&key);
				Insert(maxHeap,key);
				break;
			case 'd':
				DeleteMax(maxHeap);
				break;
			case 'p':
				PrintHeap(maxHeap);
				break;
			case 'f':
				fscanf(fi,"%d",&key);
				if(Find(maxHeap,key))
					printf("%d is in the tree.\n", key);
				else
					printf("%d is not in the tree.\n", key);
				break;
		}
	}
}

Heap* CreateHeap(int heapSize){
	Heap* temp;
	temp=malloc(sizeof(Heap));
	if(temp==NULL){
		printf("Error: The memory is Full!\n");
	} else {
		temp->Size=0;
		temp->Capacity=heapSize;
		temp->Elements=malloc(sizeof(int)*(temp->Capacity+1));
		if(temp->Elements==NULL){
			printf("Error: The memory is Full!\n");
			free(temp);
			return NULL;
		} else {
			temp->Elements[0]=BEGIN;
		}
	}
	return temp;
}

void Insert(Heap *heap, int value){
	if(heap->Size==heap->Capacity){
		printf("Insertion Error : Max heap is full.\n");
		return;
	}
	if(Find(heap,value)){
		printf("%d is already in the tree.\n",value);
		return;
	}

	int i;

	for(i=++heap->Size; i/2>0&&value>heap->Elements[i/2];i/=2){
		heap->Elements[i]=heap->Elements[i/2];
	}
	heap->Elements[i]=value;
	printf("insert %d\n",value);
}

int Find(Heap *heap, int value){
	for(int i=1;i<=heap->Size;i++){
		if(value==heap->Elements[i]){
			return TRUE;
		}
	}
	return FALSE;
}

int DeleteMax(Heap* heap){
	if(heap->Size==0){
		printf("Deletion Error : Max heap is empty!\n");
		return FALSE;
	}

	int i, Child;
	ElementType MaxElement, LastElement;

	MaxElement=heap->Elements[1];
	LastElement=heap->Elements[heap->Size--];

	for(i=1;i*2<=heap->Size;i=Child){
		Child=i*2;
		if(Child !=heap->Size && heap->Elements[Child] < heap->Elements[Child+1])
			Child++;
		
		if(LastElement < heap->Elements[Child])
			heap->Elements[i]=heap->Elements[Child];
		else break;
	}
	heap->Elements[i]=LastElement;
	return MaxElement;
}

void PrintHeap(Heap* heap){
	if(heap->Size==0){
		printf("Print Error : Max heap is empty!\n");
		return;
	}

	for(int i=1; i<=heap->Size ; i++) {
		printf("%d ",heap->Elements[i]);
	}
	printf("\n");
}
