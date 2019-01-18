#include "list.h"
#include <stdlib.h>
#include <stdio.h>

static int last_nid = -1;
static node_t* oheader = NULL;
static node_t* fheader = NULL;

void list_insert(element_t element) {
	node_t* new_node;
	node_t* otail;
	node_t* ftail;

	new_node = malloc(sizeof(node_t));
	new_node->nid = ++last_nid;
	new_node->element = element;
	new_node->oprev = NULL;
	new_node->onext = NULL;
	new_node->fprev = NULL;
	new_node->fnext = NULL;
	new_node->naccess = 0;
	new_node->leader = NULL;

	if(oheader == NULL) {
		oheader = new_node;
		fheader = new_node;
		new_node->oprev = new_node;
		new_node->fprev = new_node;
		new_node->leader = new_node;
	} else {
		otail = oheader->oprev;
		otail->onext = new_node;
		new_node->oprev = otail;
		oheader->oprev = new_node;

		ftail = fheader->fprev;
		ftail->fnext = new_node;
		new_node->fprev = ftail;
		fheader->fprev = new_node;

		if(ftail->naccess == 0) {
			new_node->leader = ftail->leader;
		} else {
			new_node->leader = new_node;
		}
	}
}

node_t* list_access(int nid) {
	node_t* node = oheader;
	node_t* leader;
	node_t* fprev;
	node_t* fnext;
	node_t* itr;
	int i;

	if(nid > last_nid)
		return NULL;
	for(i = 0; i < nid; i++) {
		node = node->onext;
	}

	node->naccess++;
	leader = node->leader;
	fprev = node->fprev;
	fnext = node->fnext;

	if(leader == node) {
		for(itr = fnext; itr != NULL && itr->leader == leader; itr = itr->fnext) {
			itr->leader = fnext;
		}
		if(leader != fheader && node->naccess == fprev->naccess)
			node->leader = fprev->leader;

	} else {
		if(fnext == NULL) {
			fheader->fprev = fprev;
			fprev->fnext = NULL;
		} else {
			fprev->fnext = fnext;
			fnext->fprev = fprev;
		}

		fprev = leader->fprev;
		fnext = leader;
		node->fprev = fprev;
		node->fnext = fnext;
		fnext->fprev = node;

		if(leader == fheader) {
			fheader = node;
			node->leader = node;
		} else {
			fprev->fnext = node;
			node->leader = node->naccess == fprev->naccess ?
				fprev->leader : node;
		}
	}

	return node;
}

void list_print_third_element() {
	node_t* node = fheader;
	int i;

	if(node == NULL)
		return;

	for(i = 0; i < 2; i++) {
		node = node->fnext;
		if(node == NULL)
			return;
	}

	printf("Solve: %u!\n", node->element);
}

void list_print() {
	list_node_t* itr;

	puts("+++++order+++++");
	for(itr = oheader; itr != NULL; itr = itr->onext) {
		printf("[%d] %u (access: %d)\n",itr->nid, itr->element, itr->naccess);
	}
	puts("+++frequency+++");
	for(itr = fheader; itr != NULL; itr = itr->fnext) {
		printf("[%d] %u (access: %d)\n",itr->nid, itr->element, itr->naccess);
	}
}
