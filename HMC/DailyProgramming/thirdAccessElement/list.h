#ifndef __LIST_H__
#define __LIST_H__

typedef struct list_node_t list_node_t, node_t;
typedef unsigned int element_t;

struct list_node_t {
	int nid;
	element_t element;
	/* Used for the order of insertions */
	list_node_t* oprev;
	list_node_t* onext;
	/* Used for the order of the frequency of access */
	list_node_t* fprev;
	list_node_t* fnext;
	int naccess;
	list_node_t* leader;
};

void list_insert(element_t element);
node_t* list_access(int nid);
void list_print();
#endif /* LIST_H */
