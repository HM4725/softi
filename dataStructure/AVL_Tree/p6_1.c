#include<stdio.h>
#include<stdlib.h>

typedef struct AVLNode* AVLTree;
typedef int ElementType;

struct AVLNode{
	ElementType Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

int Height(AVLTree);
AVLTree Insert(int,AVLTree);
void PrintInorder(AVLTree);
void DeleteTree(AVLTree);

int main(int argc, char** argv){
	FILE *fp=fopen(argv[1],"r");
	AVLTree myTree=NULL;
	int num;

	if(fp==NULL){
		printf("There is no file: %s\n",argv[1]);
		exit(-1);
	}

	while (fscanf(fp,"%d",&num) !=EOF){

		myTree = Insert(num, myTree);
		PrintInorder(myTree);
		printf("\n");
	}

	DeleteTree(myTree);
	return 0;
}

AVLTree Insert(int key,AVLTree root){
	if(root==NULL){
		root=(AVLTree)malloc(sizeof(struct AVLNode));
		root->Element=key;
		root->Left=root->Right=NULL;
		root->Height=0;
	}
	else if(root->Element>key){
		root->Left=Insert(key,root->Left);
	}
	else if(root->Element<key){
		root->Right=Insert(key,root->Right);
	}
	else {
		printf("[Error] %d already in the tree!\n",key);
	}
	
	/*Height*/
	(Height(root->Left) > Height(root->Right)) ? 
		(root->Height=Height(root->Left)+1) : (root->Height=Height(root->Right)+1) ;
	return root;
}
void PrintInorder(AVLTree root){
	if(root==NULL) return;

	PrintInorder(root->Left);
	printf("%d(%d) ",root->Element,root->Height);
	PrintInorder(root->Right);
}
void DeleteTree(AVLTree root){
	if(root==NULL) return;

	DeleteTree(root->Left);
	free(root);
	DeleteTree(root->Right);
}

int Height(AVLTree root){
	if(root==NULL)
		return -1;
	else return root->Height;
}
