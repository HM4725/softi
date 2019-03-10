#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct threaded_tree *threaded_ptr;
typedef struct treaded_tree{
	short int left_thread;
	threaded_ptr left_child;
	char data;
	threaded_ptr right_child;
	short int right_thread;
}Tree;

Tree* insertNode(Tree* root, char key);
void printInorder(Tree* root);
void deleteTree(Tree* root);

void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");
	char cv;
	char key;

	Tree* root=NULL;

	while(!feof(fi)){
		fscanf(fi,"%c",&cv);
		switch(cv){
			case'i':
				fscanf(fi,"%c",&key);
				root=insertNode(root,key);
				break;

			case'p':
				fscanf(fi,"%c",&cv);
				if(cv=='i')
					printInorder(root);
				printf("\n");
				break;
		}
	}
	deleteTree(root);
}

void deleteTree(Tree* root){
	if(root==NULL) return;

	deleteTree(root->left);
	deleteTree(root->right);
	free(root);
}

Tree* insertNode(Tree* root, char key){
	if(root==NULL){
		root=(Tree*)malloc(sizeof(struct Tree));
		if(root==NULL){
			printf("Out of space!!!\n");
		}
		else {
			root->left_thread=root->right_thread=TRUE;
			root->data=key;
			root->left_child
			root->right_child=NULL;
			printf("Insert %d\n",key);
		}
	}
	else if (key>root->value){
		root->right_child=insertNode(root->right,key);
		root->right_thread=FALSE;
	}
	else if (key<root->value){
		root->left=insertNode(root->left,key);
		root->left_thread=FALSE;
	}
	else { // key==root->value
		printf("Insertion Error: There is already %d in the tree.\n"
				,root->value);
	}
	return root;
}
void printInorder(Tree* root){
	if(root==NULL) return;

	printInorder(root->left);
	printf("%d ",root->value);
	printInorder(root->right);
}

threaded_ptr insucc(threaded_ptr tree){
	threaded_ptr temp;
	temp=tree->right_child;
	if(!tree->right_thread){
		while(!temp->left_thread)
			temp=temp->left_child;
	}
	return temp;
}
