#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HEADER 0xBABECAFE
#define TRUE 1
#define FALSE 0

typedef int ElementType;
typedef struct ListNode *List,*Position;
typedef struct ListNode{
	ElementType Element;
	Position Next;
}ListNode;

typedef struct HashTable{
	int TableSize;
	List *TheLists;
}HashTable;

void Insert(ElementType Key, HashTable* H);
Position Find(ElementType value,HashTable* H);

int main(int argc, char *argv[]){

	FILE *f;
	f=fopen(argv[1],"r");
	char index[100];
	int indexnumber;
	char *ptr1,*ptr2,*ptr3;
	char *ptrtmp[3];

	fgets(index,100,f);
	ptr1= strtok_r(index," ",&ptrtmp[0]);

	indexnumber=atoi(ptr1);
	HashTable *hs;
	hs = (HashTable*)malloc(sizeof(HashTable));
	hs->TableSize=indexnumber;
	hs->TheLists=(List*)malloc(sizeof(List)*indexnumber);
	int i;
	for(i=0;i<indexnumber;i++){
		hs->TheLists[i]=(List)malloc(sizeof(ListNode));	//header
		hs->TheLists[i]->Element=HEADER;
		hs->TheLists[i]->Next=NULL;
	}

	fgets(index, 100, f);
	ptr2=strtok_r(index," ", &ptrtmp[1]);
	while(ptr2 !=NULL){
		indexnumber =atoi(ptr2);
		Insert(indexnumber,hs);
		ptr2=strtok_r(NULL," ",&ptrtmp[1]);
	}

	Position tmp;
	fgets(index, 100, f);
	ptr3=strtok_r(index," ",&ptrtmp[2]);
	while(ptr3 !=NULL){
		indexnumber = atoi(ptr3);
		tmp=Find(indexnumber, hs);
		if(tmp==NULL)
			printf("%d is not in the table\n",indexnumber);
		else printf("%d is in the table\n",indexnumber);
		ptr3=strtok_r(NULL," ",&ptrtmp[2]);
	}
	return 0;
}

void Insert(ElementType Key, HashTable* H){
	if(Find(Key,H)){
		printf("%d is already in the table\n",Key);
		return ;
	}
	ElementType hResult=Key % H->TableSize;
	List hCell=H->TheLists[hResult];
	List nextCell=hCell;
	int i=0,nResult=hResult;
	while(i!=H->TableSize && nextCell->Next!=NULL){
		printf("%d insertion collision has been occured with number %d\n",
				Key, nextCell->Next->Element);
		i++;
		nResult=(hResult+i)%H->TableSize;
		nextCell=H->TheLists[nResult];
	}
	if(i==H->TableSize){
		printf("Hash is full\n");
		return;
	}

	Position insert=malloc(sizeof(ListNode));
	insert->Element=Key;
	insert->Next=NULL;
	nextCell->Next=insert;
	printf("%d is inserted at address %d\n",Key,nResult);

}
Position Find(ElementType value,HashTable* H){
	if(H==NULL){
		printf("error: There is no table.\n");
		return NULL;
	}
	int delta=0;
	List hCell=H->TheLists[delta];
	while(delta!=H->TableSize){
		if(hCell->Next!=NULL && hCell->Next->Element==value){
			break;
		}
		delta++;
		hCell=H->TheLists[delta];
	}
	return delta!=H->TableSize ? hCell : NULL ;
}
