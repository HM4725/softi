#include<stdio.h>
#include<stdlib.h>

#define INF 0x7FFFFFFF
#define BEGIN 0
#define NOEDGE 0
#define NIL -1
#define TRUE 1
#define FALSE 0

typedef struct Node{
	int vertex;
	int dist; //distance
	int prev;
}Node;

Node Error={0,0,NIL};

typedef struct Graph{
	int size;
	int** vertices;
	Node* nodes;
}Graph;

typedef struct Heap{
	int Capacity;
	int Size;
	Node* Element;
}Heap;

Graph CreateGraph(int size);
void printShortestPath(Graph g);
Heap* createMinHeap(int heapSize);
void insertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);

void main(int argc, char* argv[]) {
	FILE *fi = fopen(argv[1], "r");
	Graph g;
	int size;
	fscanf(fi, "%d\n",&size);
	g = CreateGraph(size+1);
	char temp = 0;
	while( temp != '\n' ) {
		int node1, node2, weight;
		fscanf(fi,"%d-%d-%d",&node1,&node2,&weight);
		g.vertices[node1][node2] = weight;
		temp = fgetc(fi);
	}
	printShortestPath(g);
}

Graph CreateGraph(int size){
	Graph g;
	g.size=size;
	g.vertices=malloc(sizeof(int*)*size);
	for(int i=0;i<size;i++){
		g.vertices[i]=malloc(sizeof(int)*size);
	}
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(i==0) g.vertices[i][j]=j;
			else if(j==0) g.vertices[i][j]=i;
			else g.vertices[i][j]=NOEDGE;
		}
	}
	g.nodes=malloc(sizeof(Node)*size);
	for(int i=1;i<size;i++){
		g.nodes[i].vertex=i;
		g.nodes[i].dist=INF;
		g.nodes[i].prev=NIL;
	}
	g.nodes[1].dist=0;
	g.nodes[1].prev=BEGIN;

	return g;
}
void printShortestPath(Graph g){
	Node shortest;
	Heap* pMinHeap=createMinHeap(g.size);
	int i,hi;
	int vrt,prev,length;
	int* course=malloc(sizeof(int)*g.size);

	for(i=1;i<g.size;i++)
			insertToMinHeap(pMinHeap,i,	g.nodes[i].dist);

	while(pMinHeap->Size!=0){
		shortest=deleteMin(pMinHeap);
		if(shortest==Error) return;
		vrt=shortest.vertex;
		
		for(i=1;i<g.size;i++){
			if(g.vertices[vrt][i]!=NOEDGE &&
					g.nodes[vrt].dist + g.vertices[vrt][i] < g.nodes[i].dist){

				g.nodes[i].dist=g.nodes[vrt].dist+g.vertices[vrt][i];
				g.nodes[i].prev=vrt;
				for(hi=1;hi<=pMinHeap->Size && pMinHeap->Element[hi].vertex!=g.nodes[i].vertex ;hi++);
				pMinHeap->Element[hi].dist=g.nodes[i].dist;
					/* heapify */
				while(hi!=1 && pMinHeap->Element[hi].dist < pMinHeap->Element[hi/2].dist){
						Node temp=pMinHeap->Element[hi];
						pMinHeap->Element[hi]=pMinHeap->Element[hi/2];
						pMinHeap->Element[hi/2]=temp;
						hi/=2;
				}
			}
		}
	}
	// print
	for(i=2;i<g.size;i++){
		length=0;
		prev=i;
		while(prev!=BEGIN){
			vrt=prev;
			prev=g.nodes[vrt].prev;
			course[length++]=vrt;
		}
		printf("1");
		for(int m=length-2;m>=0;m--)
			printf("->%d",course[m]);
		printf(" (cost : %d)\n",g.nodes[i].dist);
	}

	free(course);	

	//free heap
	free(pMinHeap->Element);
	free(pMinHeap);

	//free graph
	for(int i=0;i<g.size;i++)
		free(g.vertices[i]);
	free(g.vertices);
	free(g.nodes);
}

Heap* createMinHeap(int heapSize){
	Heap* pHeap;
	pHeap=malloc(sizeof(Heap));
	pHeap->Capacity=heapSize;
	pHeap->Size=0;
	pHeap->Element=malloc(sizeof(Node)*heapSize);

	return pHeap;
}
void insertToMinHeap(Heap* minHeap, int vertex, int distance){
	if(!minHeap){
		printf("Insertion Error: minHeap does not exist.\n");
		return;
	}
	if(minHeap->Capacity==minHeap->Size){
		printf("Insertion Error: minHeap is full.\n");
		return;
	}

	Node temp;
	temp.vertex=vertex;
	temp.dist=distance;
	int i;	
	for(i=++minHeap->Size; i/2>0 &&
			distance<minHeap->Element[i/2].dist;i/=2)
		minHeap->Element[i]=minHeap->Element[i/2];
	minHeap->Element[i]=temp;
}
Node deleteMin(Heap* minHeap){
	if(!minHeap){
		printf("Delete Error: minHeap does not exist.\n");
		return Error;
	}
	if(minHeap->Size==0){
		printf("Delete Error: minHeap is empty.\n");
		return Error;
	}

	int i, child;
	Node minElement=minHeap->Element[1];
	Node lastElement=minHeap->Element[minHeap->Size--];

	for(i=1; i*2<=minHeap->Size;i=child){
		child=i*2;
		if(child!=minHeap->Size 
				&& minHeap->Element[child].dist 
				> minHeap->Element[child+1].dist) child++;
		if(lastElement.dist > minHeap->Element[child].dist)
			minHeap->Element[i]=minHeap->Element[child];
		else break;
	}
	minHeap->Element[i]=lastElement;
	return minElement;
}
