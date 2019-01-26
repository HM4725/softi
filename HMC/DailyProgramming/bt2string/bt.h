#ifndef __BT_H__
#define __BT_H__

#define LEFT 0
#define RIGHT 1

typedef struct bt_node_t bt_node_t;

struct bt_node_t {
	int element;
	bt_node_t* left;
	bt_node_t* right;
};

#endif /* BT_H */
