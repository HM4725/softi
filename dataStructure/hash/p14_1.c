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
	if(hCell->Next!=NULL){
		printf("%d insertion collision has been occured with number %d\n",
				Key, hCell->Next->Element);
	}

	Position newCell=malloc(sizeof(ListNode));
	newCell->Element=Key;
	newCell->Next=hCell->Next;
	hCell->Next=newCell;
	printf("%d is inserted\n",Key);

	char full=TRUE;
	for(int i=0; i<H->TableSize; i++){
		if(H->TheLists[i]->Next!=NULL){
			full=FALSE;
		}
	}
	if(full){
		printf("Hash table is full\n");
	}

}
Position Find(ElementType value,HashTable* H){
	if(H==NULL){
		printf("error: There is no hashtable.\n");
		return NULL;
	}

	ElementType hResult=value % H->TableSize;
	List hCell=H->TheLists[hResult];
	Position itr;

	for(itr=hCell->Next; itr!=NULL && itr->Element!= value ;itr=itr->Next);

	return itr;
}
