#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define WALL -1
#define NOWALL 0
#define SUCCESS 1
#define FAIL 0

typedef struct _DisjointSet{
	int size_maze;
	int* ptr_arr;
} DisjointSets;

void init(DisjointSets *sets, DisjointSets *maze,int num);
int Union(DisjointSets *sets, int i, int j);
int find(DisjointSets *sets, int i);
void createMaze(DisjointSets *sets,DisjointSets *maze_print,int num);
void printMaze(DisjointSets *sets, int num);
void freeMaze(DisjointSets *set, DisjointSets *maze_print);

int main(int argc, char* argv[]){
	int num;
	DisjointSets *sets, *maze_print;
	FILE *fi=fopen(argv[1],"r");

	fscanf(fi,"%d",&num);

	sets=(DisjointSets*)malloc(sizeof(DisjointSets));
	maze_print=(DisjointSets*)malloc(sizeof(DisjointSets));

	init(sets,maze_print,num);
	createMaze(sets,maze_print,num);
	printMaze(maze_print,num);
	freeMaze(sets,maze_print);

	fclose(fi);

	return 0;
}

void init(DisjointSets *sets, DisjointSets *maze,int num){

	sets->size_maze=num*num+1;
	sets->ptr_arr=(int*)malloc(sets->size_maze*sizeof(int));
	for(int i=1; i<sets->size_maze;i++){
		sets->ptr_arr[i]=0;
	}

	maze->size_maze=2*(num+1)*num; 
	maze->ptr_arr=(int*)malloc(maze->size_maze*sizeof(int));
	for(int i=0; i<maze->size_maze;i++){
		maze->ptr_arr[i]=WALL;
	}
	maze->ptr_arr[num]=NOWALL; //Entrance
	maze->ptr_arr[maze->size_maze-num-1]=NOWALL; //EXIT
}

int Union(DisjointSets *sets, int i, int j){
	int set1=find(sets,i);
	int set2=find(sets,j);

	if(set1==set2) return FAIL;

	if(sets->ptr_arr[set1]>sets->ptr_arr[set2]){ // rank1<rank2
		sets->ptr_arr[set1]=set2;
	} else if(sets->ptr_arr[set1]<sets->ptr_arr[set2]) { // rank1>rank2
		sets->ptr_arr[set2]=set1;
	} else {
		sets->ptr_arr[set1]=set2;
		sets->ptr_arr[set2]--;
	}
	return SUCCESS;
}
//Q1. return value type이 void면 union하면 안되는 경우는 어떻게 판별?

int find(DisjointSets *sets, int i){
	return sets->ptr_arr[i]<=0 ?
		i :
		find(sets,sets->ptr_arr[i]) ;
//	sets->ptr_arr[i]=find(sets,sets->ptr_arr[i]) ; 			//Q2. rank 계산은?
}
void createMaze(DisjointSets *sets,DisjointSets *maze_print,int num){
	int location, row, column;
	int dir, wall;

	srand((unsigned int)time(NULL));

	while(find(sets,1)!=find(sets,num*num)){

		location=rand()%(num*num)+1;	// 1~(num*num)
		row=(location-1)/num;	// 0~(num-1)
		column=(location-1)%num;	// 0~(num-1)
		dir=rand()%4; // 0:E, 1:W, 2:S, 3:N

		switch(dir){

			case 0:	// East
				if(column!=num-1 &&
						Union(sets,location,location+1)){

					wall=(2*num+1)*row+num+column+1;
					maze_print->ptr_arr[wall]=NOWALL;
				}
				break;

			case 1:	// West
				if(column!=0 && 
						Union(sets,location,location-1)){

					wall=(2*num+1)*row+num+column;
					maze_print->ptr_arr[wall]=NOWALL;
				}
				break;

			case 2:	// South
				if(row!=num-1 &&
						Union(sets,location,location+num)){

					wall=(2*num+1)*(row+1)+column;
					maze_print->ptr_arr[wall]=NOWALL;
				}
				break;

			case 3:	// North
				if(row!=0 &&
						Union(sets,location,location-num)){

					wall=(2*num+1)*row+column;
					maze_print->ptr_arr[wall]=NOWALL;
				}
				break;
		}

	}
}
	

void printMaze(DisjointSets *sets, int num){
	int turn=0;
	int row=0;
	while(turn<sets->size_maze){
		if(row%2==0){	// evenRow
			for(int i=0;i<num; i++){
				if(sets->ptr_arr[turn]==WALL){
					printf(" -");
				} else printf("  ");
				turn++;
			}
			printf("\n");
		} else {	// oddRow
			for(int i=0; i<num+1; i++){
				if(sets->ptr_arr[turn]==WALL){
					printf("| ");
				} else printf("  ");
				turn++;
			}
			printf("\n");
		}
		row++;
	}
}

void freeMaze(DisjointSets *set, DisjointSets *maze_print){
	free(set->ptr_arr);
	free(set);
	free(maze_print->ptr_arr);
	free(maze_print);
}
