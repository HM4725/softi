#include <stdlib.h>
#include <time.h>
#include "bt.h"

static int count = 0;

enum child {
	NONE, LEFT, RIGHT, BOTH
};

static void bt_make_nodes(bt_node_t* parent) {
	int child = rand() % 4;

	switch(child) {
		case NONE:
			break;
		case LEFT:
			parent->left = malloc(sizeof(bt_node_t));
			parent->left->element = rand() % 10000;
			bt_make_nodes(parent->left);
			break;
		case RIGHT:
			parent->right = malloc(sizeof(bt_node_t));
			parent->right->element = rand() % 10000;
			bt_make_nodes(parent->right)
			break;
		case BOTH:
			parent->left = malloc(sizeof(bt_node_t));
			parent->left->element = rand() % 10000;
			bt_make_nodes(parent->left);
			parent->right = malloc(sizeof(bt_node_t));
			parent->right->element = rand() % 10000;
			bt_make_nodes(parent->right)
			break;
	}
};

bt_node_t* bt_make_entry() {
	bt_node_t* root;
	
	srand(time(NULL));

	root = malloc(sizeof(bt_node_t));
	root->element = rand();

	bt_make_nodes(root);

	return root;
}

char* bt2string(bt_node_t* node, int pid, char left) {
	int id = ++count;
	static char* begin = NULL;
	static char* end = NULL;
	int* itr;

	if(node->left)
		bt2string(node->left, id, LEFT);
	if(node->right)
		bt2string(node->left, id, RIGHT);

	if(begin == NULL) {
		begin = malloc(sizeof(int) * 4);
		end = begin + sizeof(int) * 4;
	}




	

}

bt_node_t* string2bt(char* str) {


}
