#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENDOFARR -86142747
#define EDGE 1
#define NOEDGE 0
#define INPUT_FAIL -1

//typedef struct _Queue* Queue;
typedef struct _Graph* Graph;
/*
struct _Queue
{
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};*/

struct _Graph
{
	int size;
	int* node;
	int** matrix;
};

Graph CreateGraph(int* nodes);
void InsertEdge(Graph G, int a, int b);

//void DeleteGraph(Graph G);
//void Topsort(Graph G);

//Queue MakeNewQueue(int X);
//int IsEmpty(Queue Q);
//int IsFull(Queue Q);
//int Dequeue(Queue Q);
//void Enqueue(Queue Q, int X);
//void DeleteQueue(Queue Q);
//void MakeEmpty(Queue Q);

int main(int argc, char** argv){
	FILE *fi=fopen(argv[1],"r");
	char strLine1[200];
	char strLine2[40000];
	char *seg, *oper;
	int tempNodes[100], count=1;
	int lvalue, rvalue;	
	// strLine2: (lvalue-rvalue)s

	/* Get 2 lines from input.txt */
	fgets(strLine1,200,fi);
	fgets(strLine2,40000,fi);

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

	/* print the matrix */
	printf("  ");
	for(int i=0;i<graph->size;i++)
		printf("%2d",graph->node[i]);
	printf("\n");
	for(int i=0;i<graph->size;i++){
		printf("%2d",graph->node[i]);
		for(int j=0;j<graph->size;j++){
			printf("%2d",graph->matrix[i][j]);
		}
		printf("\n");
	}

	/* close input.txt */
	fclose(fi);
}

Graph CreateGraph(int* nodes){
	int size;
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
