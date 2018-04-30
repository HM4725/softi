#include<stdio.h>
#include<stdlib.h>

typedef struct node* PNODE;
typedef struct node{
	int a;
	PNODE pn;
}NODE;

int main(){
	PNODE test1;
	test1=(PNODE)malloc(sizeof(NODE));
	test1->a=0;
	test1->pn=NULL;
	printf("%p\n",&test1);

	PNODE test2;
	test2=(PNODE)malloc(sizeof(NODE));
	test2->a=0;
	test2->pn=NULL;

	test1->pn=test2;

	printf("test2: %p\n",test2);
	printf("test1->pn: %p\n",test1->pn);

	free(test2);

	if(test1->pn==NULL){
		puts("After free(test2), test1->pn also become NULL");
	}
	else {
		puts("After free(test2), there remains the address of test2 in test1->pn.");
	}

	printf("test2: %p\n",test2);
	printf("test1->pn: %p\n",test1->pn);
	return 0;
}

/* heap영역의 동적할당이 해제되더라도 
   포인터 변수안의 데이터인 주소값은 그대로 남아있음 
*/
