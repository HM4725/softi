#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLengthOfFirstLine 300
#define MaxLengthOfSecondLine 60000 

#define ENDOFARR -0x86142747
#define EDGE 1
#define NOEDGE 0
#define INPUT_FAIL -1
#define DEQUEUE_FAIL -0x80000000
#define SORTED -1

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue
{
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

struct _Graph
{
	int size;
	int* node;
	int** matrix;
};

Graph CreateGraph(int* nodes);
void InsertEdge(Graph G, int a, int b);

void DeleteGraph(Graph G);
void Topsort(Graph G);

Queue MakeNewQueue(int X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
int Dequeue(Queue Q);
void Enqueue(Queue Q, int X);
void DeleteQueue(Queue Q);

int main(int argc, char** argv){
	FILE *fi=fopen(argv[1],"r");
	char strLine1[MaxLengthOfFirstLine];
	char strLine2[MaxLengthOfSecondLine];
	char *seg, *oper;
	int tempNodes[100], count=1;
	int lvalue, rvalue;	
	// strLine2: (lvalue-rvalue)s

	/* Get 2 lines from input.txt */
	fgets(strLine1,MaxLengthOfFirstLine,fi);
	fgets(strLine2,MaxLengthOfSecondLine,fi);

	/* Make a integer array from strLine1 */
	seg=strtok(strLine1," ");
	tempNodes[0]=atoi(seg);
	if(tempNodes[0]==ENDOFARR) return INPUT_FAIL;
	while(seg=strtok(NULL," ")){
		tempNodes[count++]=atoi(seg);
		if(tempNodes[count-1]==ENDOFARR) return INPUT_FAIL;
	}
	tempNodes[count]=ENDOFARR;

	/* Make a graph from tempNodes */
	Graph graph=CreateGraph(tempNodes);

	/* Make the matrix from strLine2 */
	seg=strtok(strLine2," ");
	while(seg){

		for(oper=seg;*oper!='-';oper++);
		lvalue=atoi(seg);	// atoi: read until nondigit ('-')
		rvalue=atoi(oper+1);	// until ' '

		InsertEdge(graph,lvalue,rvalue);
		
		seg=strtok(NULL," ");
	}

	/* Topological sort of graph */
	Topsort(graph);
		
	/* free */
	DeleteGraph(graph);

	/* close input.txt */
	fclose(fi);


}
Graph CreateGraph(int* nodes){
	int size;

	if(nodes==NULL) {
		printf("Error: There is no node!\n");
		return NULL;
	}

	Graph graph=malloc(sizeof(struct _Graph));

	/* load graph->size */
	for(size=0; nodes[size]!=ENDOFARR ; size++);
	graph->size=size;

	/* load graph->node */
	graph->node=nodes;

	/* load graph->matrix */
	int** tempMatrix=malloc(sizeof(int*)*size);
	for(int i=0; i<size; i++){
		tempMatrix[i]=malloc(sizeof(int)*size);
	}
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			tempMatrix[i][j]=NOEDGE;
		}
	}
	graph->matrix=tempMatrix;

	return graph;
}
void InsertEdge(Graph G, int a, int b){
	int m,n;	// mth row, nth column
	for(m=0; m<G->size && G->node[m]!=a ; m++);
	for(n=0; n<G->size && G->node[n]!=b ; n++);

	if(m==G->size || n==G->size ) return;

	G->matrix[m][n]=EDGE;
}
void DeleteGraph(Graph G){
	// Do not free(Graph->node)
	// Graph->node is in main, not in heap
	for(int i=0; i<G->size; i++){
		free(G->matrix[i]);
	}
	free(G->matrix);
	free(G);
}
void Topsort(Graph G) {
	Queue Q=MakeNewQueue(sizeof(int)*G->size);
	int* InDegrees=malloc(sizeof(int)*G->size);
	int* Buffer=malloc(sizeof(int)*G->size);
	int bufferSize=0, tmp, V, rowV;

	/* make an array of in-degrees */
	for(int i=0;i<G->size;i++){
		InDegrees[i]=0;
	}
	for(int i=0;i<G->size;i++){
		for(int j=0;j<G->size;j++){
			if(G->matrix[j][i]==EDGE)
				InDegrees[i]++;
		}
	}

	/* Topsort first phase */
	for(int i=0;i<G->size;i++){
		if(InDegrees[i]==0){
			Buffer[bufferSize++]=G->node[i];
			InDegrees[i]=SORTED;
		}
	}
		// BubbleSort for the keys of same priority 
	for(int i=0;i<bufferSize-1;i++){
		for(int j=i+1;j<bufferSize;j++){
			if(Buffer[i]>Buffer[j]){
				tmp=Buffer[i];
				Buffer[i]=Buffer[j];
				Buffer[j]=tmp;
			}
		}
	}
	for(int i=0;i<bufferSize;i++){
		Enqueue(Q,Buffer[i]);
	}

	while(!IsEmpty(Q)){
		/* Topsort next phases */

		V=Dequeue(Q);

		for(rowV=0;G->node[rowV]!=V; rowV++);	// G->node[rowV]==V
		for(int i=0; i<G->size; i++){
			if(G->matrix[rowV][i]==EDGE){
				G->matrix[rowV][i]=NOEDGE;
				InDegrees[i]--;
			}
		}
		printf("%d ",V);

		bufferSize=0;
		for(int i=0; i<G->size;i++){
			if(InDegrees[i]==0){
				Buffer[bufferSize++]=G->node[i];
				InDegrees[i]=SORTED;
			}
		}

		if(bufferSize!=0){

			for(int i=0;i<bufferSize-1;i++){
				for(int j=i+1;j<bufferSize;j++){
					if(Buffer[i]>Buffer[j]){
						tmp=Buffer[i];
						Buffer[i]=Buffer[j];
						Buffer[j]=tmp;
					}
				}
			}

			for(int i=0;i<bufferSize;i++){
				Enqueue(Q,Buffer[i]);
			}
		}
	}
	printf("\n");

	/* Free tools of Topological Sort */
	free(InDegrees);
	free(Buffer);
	DeleteQueue(Q);
}
// big-O notation: V*V or V*b*b? / not V+E !!

Queue MakeNewQueue(int X){
	Queue queue;
	queue=malloc(sizeof(struct _Queue));
	queue->key=malloc(sizeof(int)*X);
	queue->first=0;
	queue->rear=-1;
	queue->qsize=0;
	queue->max_queue_size=X;

	return queue;
}
int IsEmpty(Queue Q){
	return Q->qsize==0;
}
int IsFull(Queue Q){
	return Q->qsize==Q->max_queue_size;
}
int Dequeue(Queue Q){
	if(IsEmpty(Q)){
		printf("ERROR: The queue is empty!\n");
		return DEQUEUE_FAIL;
	}
	int hold=Q->key[Q->first];

	Q->first = (Q->first + 1) % (Q->max_queue_size);
	Q->qsize--;

	return hold;
}
void Enqueue(Queue Q, int X){
	if(IsFull(Q)){
		printf("ERROR: The queue is full!\n");
		return ;
	}
	Q->rear = (Q->rear + 1) % (Q->max_queue_size) ;
	Q->key[Q->rear]=X;
	Q->qsize++;
}
void DeleteQueue(Queue Q){
	free(Q->key);
	free(Q);
}
