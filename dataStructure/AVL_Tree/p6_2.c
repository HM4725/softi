#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
typedef struct AVLNode *AVLTree, *Position;
typedef struct AVLNode {
	ElementType Element;
	AVLTree Left;
	AVLTree Right;
	int Height;
}AVLNode;


int Height(AVLTree);
AVLTree Insert(int,AVLTree);
void PrintInorder(AVLTree);
void DeleteTree(AVLTree);

typedef Position (*ROTATE)(Position);

Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);

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
	ROTATE rotate;

	if(root==NULL){
		root=(AVLTree)malloc(sizeof(AVLNode));
		if(root==NULL){
			printf("Error!");
			return root;
		}
		root->Element=key;
		root->Left=root->Right=NULL;
		root->Height=0;
	} else if(root->Element>key){
		root->Left=Insert(key,root->Left);
		if(Height(root->Left)-Height(root->Right)==2){
			if(root->Left->Element>key){
				rotate=SingleRotateWithLeft;
			} else {
				rotate=DoubleRotateWithLeft;
			}
			root=rotate(root);
		}
	} else if(root->Element<key){
		root->Right=Insert(key,root->Right);
		if(Height(root->Right)-Height(root->Left)==2){
			if(root->Right->Element<key){
				rotate=SingleRotateWithRight;
			} else {
				rotate=DoubleRotateWithRight;
			}
			root=rotate(root);
		}
	} else {
		printf("[Error] %d already in the tree!\n",key);
	}
	
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

Position SingleRotateWithLeft(Position node){
	Position temp=node->Left;
	node->Left=temp->Right;
	temp->Right=node;

	(Height(temp->Left) > Height(temp->Right)) ? 
		(temp->Height=Height(temp->Left)+1) : (temp->Height=Height(temp->Right)+1) ;
	(Height(node->Left) > Height(node->Right)) ? 
		(node->Height=Height(node->Left)+1) : (node->Height=Height(node->Right)+1) ;
	return temp;
}
Position SingleRotateWithRight(Position node){
	Position temp=node->Right;
	node->Right=temp->Left;
	temp->Left=node;

	(Height(temp->Left) > Height(temp->Right)) ? 
		(temp->Height=Height(temp->Left)+1) : (temp->Height=Height(temp->Right)+1) ;
	(Height(node->Left) > Height(node->Right)) ? 
		(node->Height=Height(node->Left)+1) : (node->Height=Height(node->Right)+1) ;
	return temp;
}
Position DoubleRotateWithLeft(Position node){
	node->Left=SingleRotateWithRight(node->Left);
	return SingleRotateWithLeft(node);
}
Position DoubleRotateWithRight(Position node){
	node->Right=SingleRotateWithLeft(node->Right);
	return SingleRotateWithRight(node);
}
