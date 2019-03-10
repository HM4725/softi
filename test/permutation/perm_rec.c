#include<stdio.h>
#define swap(x,y,z) { z=x; x=y; y=z; } 

int count=0;

void perm(char* list, int i, int n){
	int j, temp;
	if (i==n){
		for(j=0; j<=n; j++){
			printf("%c",list[j]);
		}
		printf("\n");
		count++;
	} else {
		for(j=i; j<=n; j++){
			swap(list[i], list[j],temp);
			perm(list, i+1, n);
			swap(list[i], list[j],temp);
		}
	}
}

void main(){
	char list[12]="hello world";
	perm(list,5,10);
	printf("total:%d\n",count);
}
