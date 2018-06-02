#include<stdio.h>
#include<stdlib.h>

#define UNSUCCESS 0x80000000
#define TRUE 1
#define FALSE 0
#define EDGE 1
#define NOEDGE 0
#define VISIT 1
#define NOVISIT 0


typedef struct Graph{
	int num;
	int** weight;
	int* check_visit;
}graph;

typedef struct Stack{
	int* content;
	int top;
	int max_stack_size;
}stack;

typedef struct CircularQueue{
	int* content;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
}queue;

graph makeGraph(FILE* fi);
//void DFS_recursive(graph g,int start,int end);
//void DFS_iterative(graph g,int start,int end);
void BFS_search(graph g,int start, int end);

stack* create_stack(int num);
void push(stack* s,int value);
int pop(stack* s);
void close_stack(stack* s);
queue* create_queue(int size);
void enqueue(queue* q,int value);
int dequeue(queue* q);
void close_queue(queue* q);

void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");

	graph g = makeGraph(fi);
	if(g.num==0 &&
			g.weight==NULL &&
			g.check_visit==NULL){
		printf("ERROR: g was made wrongly (in main)\n");
		return;
	}

	int start, end;
	fscanf(fi,"%d-%d",&start,&end);
	
/*	printf("DFS recursive : ");
	DFS_recursive(g, start, end);
	if(g.num < end)
		printf(“cannot find”);
	else if(g.check_visit[end-1] == 0)
		printf("cannot find");

	printf("\nDFS iterative : ");
	DFS_iterative(g, start, end); */

	printf("\nBFS : ");
	BFS_search(g, start, end);
	printf("\n");

	/* free and close */
	for(int i=0;i<g.num;i++){
		free(g.weight[i]);
	}
	free(g.weight);
	free(g.check_visit);
	fclose(fi);
}

graph makeGraph(FILE* fi){
	int size,start,end;
	fscanf(fi,"%d",&size);
	char success=TRUE, endOfLine=0;
	/* if success==FALSE: trap */

	graph error={0,NULL,NULL};

	/* allocate graph */
	graph g;
	g.num=size;
	g.weight=malloc(sizeof(int*)*(size+1));
	if(g.weight==NULL){
		success=FALSE;
	} else {
		for(int i=0;i<=size;i++){
			g.weight[i]=malloc(sizeof(int)*(size+1));
			if(g.weight[i]==NULL) success=FALSE;
		}
	}
	g.check_visit=malloc(sizeof(int)*size+1);
	if(g.check_visit==NULL) success=FALSE;


	/* normal flow */
	if(success=TRUE) {
		for(int i=1;i<=size;i++){
			g.check_visit[i]=NOVISIT;
		}
		for(int i=0;i<=size;i++){
			for(int j=0;j<=size;j++){
				if(i==0){
					g.weight[i][j]=j;
				} else if(j==0){
					g.weight[i][j]=i;
				} else {
					g.weight[i][j]=NOEDGE;
				}
			}
		}
		while(endOfLine!='\n'){
			fscanf(fi,"%d-%d",&start,&end);
			g.weight[start][end]=EDGE;
			endOfLine=fgetc(fi);
		}
		return g;
	}


	/* Trap Handler */
	else {
		printf("ERROR: Ran out of available memory (in makeGraph)\n");
		if(g.weight!=NULL){
			for(int i=0;i<=size;i++){
				if(g.weight[i]!=NULL) free(g.weight[i]);
			}
			free(g.weight);
		}
		if(g.check_visit!=NULL) free(g.check_visit);

		return error;
	}
}
//void DFS_recursive(graph g,int start,int end);
//void DFS_iterative(graph g,int start,int end);

void BFS_search(graph g,int start, int end){
	queue* pQueue=create_queue(g.num);
	if(pQueue==NULL){
		printf("ERROR: Queue is not created (in BFS)\n");
		return;
	}

	int loc;
	char arriveInEnd=FALSE;

	enqueue(pQueue,start);
	g.check_visit[start]=VISIT;

	while(pQueue->qsize!=0){
		loc=dequeue(pQueue);
		if(loc==UNSUCCESS){
			break;
		}
		printf("%d ",loc);
		if(loc==end){
			arriveInEnd=TRUE;
			break;
		}
		for(int i=1;i<=g.num;i++){
			if(g.weight[loc][i]==EDGE && g.check_visit[i]==NOVISIT){
				enqueue(pQueue,i);
				g.check_visit[i]=VISIT;
			}
		}
	}
	
	printf("%s\n",arriveInEnd ? "" : "cannot find" );

	close_queue(pQueue);
}

stack* create_stack(int num){
	stack* pStack=malloc(sizeof(stack));
	if(pStack==NULL){
		printf("ERROR: Ran out of available memory (in create_stack)\n");
		return NULL;	//in caller
	}
	pStack->max_stack_size=num;
	pStack->top=-1;
	pStack->content=malloc(sizeof(int)*num);
	if(pStack->content==NULL){
		printf("ERROR: Ran out of available memory (in create_stack)\n");
		return NULL;
	}

	return pStack;
}

void push(stack* s,int value){
	if(value==UNSUCCESS){
		printf("ERROR: Not allowed input (in push)\n");
		return;
	}
	if(s==NULL) {
		printf("ERROR: There is no stack (in push)\n");
		return;
	}
	if(s->content==NULL){
		printf("ERROR: There is no array of stack (in push)\n");
	}
	if(s->top+1==s->max_stack_size){
		printf("ERROR: Stack is full (in push)\n");
		return;
	}

	/* normal flow */
	s->content[++s->top]=value;
}
int pop(stack* s){
	if(s==NULL){
		printf("ERROR: There is no stack (in pop)\n");
		return UNSUCCESS;	//WHEN UNSUCCESS -> in caller
	}
	if(s->content==NULL){
		printf("ERROR: There is no array of stack (in pop)\n");
		return UNSUCCESS;
	}
	if(s->top==-1){
		printf("ERROR: Stack is empty (in pop)\n");
		return UNSUCCESS;
	}

	/* normal flow */
	return s->content[s->top--];
}
void close_stack(stack* s){
	/* when stack was improperly allocated  */
	if(s==NULL){
		printf("ERROR: There is no stack (in close_stack)\n");
		return;
	}
	if(s->content==NULL){
		printf("ERROR: There is no array of stack (in close_stack)\n");
		free(s);	/* because stack was allocated */
		return;
	}

	/* when stack was properly allocated: normal flow */
	free(s->content);
	free(s);
}

queue* create_queue(int size){
	queue* pQueue=malloc(sizeof(queue));
	if(pQueue==NULL){
		printf("ERROR: Ran out of available memory (in create_queue)\n");
		return NULL;
	}
	pQueue->max_queue_size=size;
	pQueue->first=0;
	pQueue->rear=-1;
	pQueue->qsize=0;
	pQueue->content=malloc(sizeof(int)*size);
	if(pQueue->content==NULL){
		printf("ERROR: Ran out of available memory (in create_queue)\n");
		return NULL;
	}

	return pQueue;
}
void enqueue(queue* q,int value){
	if(value==UNSUCCESS){
		printf("ERROR: Not allowed input (in enqueue)\n");
		return;
	}
	if(q==NULL) {
		printf("ERROR: There is no queue (in enqueue)\n");
		return;
	}
	if(q->content==NULL){
		printf("ERROR: There is no array of queue (in enqueue)\n");
		return;
	}
	if(q->qsize==q->max_queue_size){
		printf("ERROR: Queue is full (in enqueue)\n");
		return;
	}

	/* normal flow */
	q->rear=(q->rear+1) % q->max_queue_size;
	q->content[q->rear]=value;
	q->qsize++;
}
int dequeue(queue* q){
	if(q==NULL) {
		printf("ERROR: There is no queue (in dequeue)\n");
		return UNSUCCESS;
	}
	if(q->content==NULL){
		printf("ERROR: There is no array of queue (in dequeue)\n");
		return UNSUCCESS;
	}
	if(q->qsize==0){
		printf("ERROR: Queue is empty (in dequeue)\n");
		return UNSUCCESS;
	}

	/* normal flow */
	int temp=q->content[q->first];
	q->first=(q->first+1) % q->max_queue_size;
	q->qsize--;
	return temp;
}
	
void close_queue(queue* q){
	/* when queue was improperly allocated  */
	if(q==NULL){
		printf("ERROR: There is no queue (in close_queue)\n");
		return;
	}
	if(q->content==NULL){
		printf("ERROR: There is no array of queue (in close_queue)\n");
		free(q);	/* because queue was allocated */
		return;
	}

	/* when q was properly allocated: normal flow */
	free(q->content);
	free(q);
}
