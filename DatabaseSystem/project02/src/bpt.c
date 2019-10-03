/*
 *  bpt.c  
 */

#include "bpt.h"

// GLOBALS.

FILE * db = NULL;

header_page_t * headpg = NULL;

// FUNCTION DEFINITIONS.

// OUTPUT AND UTILITIES

/* Traces the path from the root to a leaf, searching
 * by key.  Displays information about the path
 * if the verbose flag is set.
 * Returns the leaf containing the given key.
 */
node * find_leaf(int64_t key) {

    int i = 0;
    node * c = headpg->root;
    if (c == NULL) {
        return c;
    }
    while (!c->is_leaf) {
        i = 0;
        while (i < c->num_keys) {
            if (key >= c->keys[i]) i++;
            else break;
        }
        c = (node *)c->pointers[i];
    }
    return c;
}


/* Finds and returns the record to which
 * a key refers.
 */
record * find_record(int64_t key){

	int i = 0;
	node * c = find_leaf(key);
    if (c == NULL) return NULL;
    for (i = 0; i < c->num_keys; i++)
        if (c->keys[i] == key) break;
    if (i == c->num_keys) 
        return NULL;
    else
        return (record *)c->pointers[i];
}

char * find(int64_t key) {
	if(db==NULL){
		fprintf(stderr,"ERROR: No database is selected.\n");
		return NULL;
	}

	record * rec = find_record(key);
	if(rec == NULL){
		fprintf(stderr,"ERROR: no record\n");
		return NULL;
	}
    return rec->value;
}

/* Finds the appropriate place to
 * split a node that is too big into two.
 */
int cut( int length ) {
    if (length % 2 == 0)
        return length/2;
    else
        return length/2 + 1;
}


// INSERTION

/* Creates a new record to hold the value
 * to which a key refers.
 */
record * make_record(char* value) {
    record * new_record = (record *)malloc(sizeof(record));
    if (new_record == NULL) {
        perror("Record creation.");
        exit(EXIT_FAILURE);
    }
    else {
		memcpy(new_record->value, value, 120);
    }
    return new_record;
}


/* Creates a new general node, which can be adapted
 * to serve as either a leaf or an internal node.
 */
node * make_node( free_page_t* free ) {
	if (free == NULL || free->type != FREE) {
		fprintf(stderr,"parameter free == NULL"
				" (in make_node)\n");
		return NULL;
	}
    node * new_node;
    new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        perror("Node creation.");
        exit(EXIT_FAILURE);
	}
	new_node->type = INTERNAL;			// new
	new_node->pagenum = free->pagenum;	// new
    new_node->pointers = malloc( INTERNAL_ORDER * sizeof(void *) );
    if (new_node->pointers == NULL) {
        perror("New node pointers array.");
        exit(EXIT_FAILURE);
    }
	memset(new_node->pointers, 0, INTERNAL_ORDER * sizeof(void *));
    new_node->coffset = malloc( INTERNAL_ORDER * sizeof(uint64_t) );
    if (new_node->coffset == NULL) {
        perror("New node coffsets array.");
        exit(EXIT_FAILURE);
    }
	memset(new_node->coffset, 0, INTERNAL_ORDER * sizeof(uint64_t) );
	new_node->rsoffset = DISUSED;
    new_node->keys = malloc( (INTERNAL_ORDER - 1) * sizeof(int64_t));
    if (new_node->keys == NULL) {
        perror("New node keys array.");
        exit(EXIT_FAILURE);
    }
	memset(new_node->keys, 0, (INTERNAL_ORDER - 1) * sizeof(int64_t));
    new_node->parent = NULL;
	new_node->poffset = NO_NODE_PAGE;
    new_node->is_leaf = false;
    new_node->num_keys = 0;

	mem_dealloc_free_page(free);
    return new_node;
}

/* Creates a new leaf by creating a node
 * and then adapting it appropriately.
 */
node * make_leaf( free_page_t* fpage ) {
    node * leaf = make_node(fpage);
	if(leaf == NULL){
		return NULL;
	}
	leaf->type = LEAF;
	free(leaf->pointers);
    leaf->pointers = malloc( LEAF_ORDER * sizeof(void *) );
    if (leaf->pointers == NULL) {
        perror("leaf node pointers array.");
        exit(EXIT_FAILURE);
    }
	memset(leaf->pointers, 0, LEAF_ORDER * sizeof(void *));
	free(leaf->coffset);
	leaf->coffset = NULL;
	free(leaf->keys);
    leaf->keys = malloc( (LEAF_ORDER - 1) * sizeof(int64_t) );
    if (leaf->keys == NULL) {
        perror("leaf node keys array.");
        exit(EXIT_FAILURE);
    }
	memset(leaf->keys, 0, (LEAF_ORDER -1) * sizeof(int64_t));
    leaf->is_leaf = true;
    return leaf;
}

free_page_t* select_free_page(){
	assert( db != NULL );
	assert( headpg != NULL );

	if(headpg->free == NULL){
		return NULL;
	} else {	// [HEAD] [FREE] X
		free_page_t *before, *after;
		after = headpg->free;
		if(after->next == NULL){
			headpg->foffset = NO_FREE_PAGE;
			headpg->free = NULL;
			file_write_page(0, (page_t*)headpg);
			return after;
		} else {	// [HEAD] [FREE] [FREE] ...
			while(after->next != NULL){
				before = after;
				after = before->next;
			}
			before->nfoffset = NO_FREE_PAGE;
			before->next = NULL;
			file_write_page(before->pagenum, (page_t*)before);
			return after;
		}
	}
}

free_page_t* free_page(){
	free_page_t* free;
	free = select_free_page();

	if(free == NULL){
		file_alloc_page();
		free = select_free_page();
	}
	return free;
}

/* Helper function used in insert_into_parent
 * to find the index of the parent's pointer to 
 * the node to the left of the key to be inserted.
 */
int get_left_index(node * parent, node * left) {

    int left_index = 0;
    while (left_index <= parent->num_keys && 
            parent->pointers[left_index] != left)
        left_index++;
    return left_index;
}

/* Inserts a new pointer to a record and its corresponding
 * key into a leaf.
 * Returns the altered leaf.
 */
node * insert_into_leaf( node * leaf, int64_t key, record * pointer ) {

    int i, insertion_point;

    insertion_point = 0;
    while (insertion_point < leaf->num_keys && leaf->keys[insertion_point] < key)
        insertion_point++;

    for (i = leaf->num_keys; i > insertion_point; i--) {
        leaf->keys[i] = leaf->keys[i - 1];
        leaf->pointers[i] = leaf->pointers[i - 1];
    }
    leaf->keys[insertion_point] = key;
    leaf->pointers[insertion_point] = pointer;
    leaf->num_keys++;

	file_write_page(leaf->pagenum, (page_t*)leaf);
    return leaf;
}


/* Inserts a new key and pointer
 * to a new record into a leaf so as to exceed
 * the tree's order, causing the leaf to be split
 * in half.
 */
node * insert_into_leaf_after_splitting(node * root, node * leaf, int64_t key, record * pointer) {

    node * new_leaf;
    int * temp_keys;
    void ** temp_pointers;
    int insertion_index, split, new_key, i, j;

    new_leaf = make_leaf(free_page());

    temp_keys = malloc( LEAF_ORDER * sizeof(int64_t) );
    if (temp_keys == NULL) {
        perror("Temporary keys array.");
        exit(EXIT_FAILURE);
    }

    temp_pointers = malloc( LEAF_ORDER * sizeof(void *) );
    if (temp_pointers == NULL) {
        perror("Temporary pointers array.");
        exit(EXIT_FAILURE);
    }

    insertion_index = 0;
    while (insertion_index < LEAF_ORDER - 1 && leaf->keys[insertion_index] < key)
        insertion_index++;

    for (i = 0, j = 0; i < leaf->num_keys; i++, j++) {
        if (j == insertion_index) j++;
        temp_keys[j] = leaf->keys[i];
        temp_pointers[j] = leaf->pointers[i];
    }

    temp_keys[insertion_index] = key;
    temp_pointers[insertion_index] = pointer;

    leaf->num_keys = 0;

    split = cut(LEAF_ORDER - 1);

    for (i = 0; i < split; i++) {
        leaf->pointers[i] = temp_pointers[i];
        leaf->keys[i] = temp_keys[i];
        leaf->num_keys++;
    }

    for (i = split, j = 0; i < LEAF_ORDER; i++, j++) {
        new_leaf->pointers[j] = temp_pointers[i];
        new_leaf->keys[j] = temp_keys[i];
        new_leaf->num_keys++;
    }

    free(temp_pointers);
    free(temp_keys);

    new_leaf->pointers[LEAF_ORDER - 1] = leaf->pointers[LEAF_ORDER - 1];
	new_leaf->rsoffset = leaf->rsoffset;

    leaf->pointers[LEAF_ORDER - 1] = new_leaf;
	leaf->rsoffset = new_leaf->pagenum * PAGESZ;

    for (i = leaf->num_keys; i < LEAF_ORDER - 1; i++)
        leaf->pointers[i] = NULL;
    for (i = new_leaf->num_keys; i < LEAF_ORDER - 1; i++)
        new_leaf->pointers[i] = NULL;

    new_leaf->parent = leaf->parent;
	new_leaf->poffset = leaf->poffset;
    new_key = new_leaf->keys[0];

    return insert_into_parent(root, leaf, new_key, new_leaf);
}


/* Inserts a new key and pointer to a node
 * into a node into which these can fit
 * without violating the B+ tree properties.
 */
node * insert_into_node(node * root, node * n, 
        int left_index, int64_t key, node * right) {
    int i;

    for (i = n->num_keys; i > left_index; i--) {
        n->pointers[i + 1] = n->pointers[i];
		n->coffset[i + 1] = n->coffset[i];
        n->keys[i] = n->keys[i - 1];
    }
    n->pointers[left_index + 1] = right;
	n->coffset[left_index + 1] = right->pagenum * PAGESZ;
    n->keys[left_index] = key;
    n->num_keys++;

	file_write_page(n->pagenum, (page_t*)n);
    return root;
}


/* Inserts a new key and pointer to a node
 * into a node, causing the node's size to exceed
 * the order, and causing the node to split into two.
 */
node * insert_into_node_after_splitting(node * root, node * old_node, int left_index, 
        int64_t key, node * right) {

    int i, j, split, k_prime;
    node * new_node, * child;
    int * temp_keys;
    node ** temp_pointers;
	uint64_t* temp_coffset;

    /* First create a temporary set of keys and pointers
     * to hold everything in order, including
     * the new key and pointer, inserted in their
     * correct places. 
     * Then create a new node and copy half of the 
     * keys and pointers to the old node and
     * the other half to the new.
     */

    temp_pointers = malloc( (INTERNAL_ORDER + 1) * sizeof(node *) );
    if (temp_pointers == NULL) {
        perror("Temporary pointers array for splitting nodes.");
        exit(EXIT_FAILURE);
    }
    temp_coffset = malloc( (INTERNAL_ORDER + 1) * sizeof(uint64_t) );
    if (temp_coffset == NULL) {
        perror("Temporary coffset array for splitting nodes.");
        exit(EXIT_FAILURE);
    }
    temp_keys = malloc( INTERNAL_ORDER * sizeof(int64_t) );
    if (temp_keys == NULL) {
        perror("Temporary keys array for splitting nodes.");
        exit(EXIT_FAILURE);
    }

    for (i = 0, j = 0; i < old_node->num_keys + 1; i++, j++) {
        if (j == left_index + 1) j++;
        temp_pointers[j] = old_node->pointers[i];
		temp_coffset[j] = old_node->coffset[i];
    }

    for (i = 0, j = 0; i < old_node->num_keys; i++, j++) {
        if (j == left_index) j++;
        temp_keys[j] = old_node->keys[i];
    }

    temp_pointers[left_index + 1] = right;
	temp_coffset[left_index + 1] = right->pagenum * PAGESZ;
    temp_keys[left_index] = key;

    /* Create the new node and copy
     * half the keys and pointers to the
     * old and half to the new.
     */  
    split = cut(INTERNAL_ORDER);
    new_node = make_node(free_page());
    old_node->num_keys = 0;
    for (i = 0; i < split - 1; i++) {
        old_node->pointers[i] = temp_pointers[i];
		old_node->coffset[i] = temp_coffset[i];
        old_node->keys[i] = temp_keys[i];
        old_node->num_keys++;
    }
    old_node->pointers[i] = temp_pointers[i];
    k_prime = temp_keys[split - 1];
    for (++i, j = 0; i < INTERNAL_ORDER; i++, j++) {
        new_node->pointers[j] = temp_pointers[i];
		new_node->coffset[j] = temp_coffset[i];
        new_node->keys[j] = temp_keys[i];
        new_node->num_keys++;
    }
    new_node->pointers[j] = temp_pointers[i];
	new_node->coffset[j] = temp_coffset[i];

    free(temp_pointers);
	free(temp_coffset);
    free(temp_keys);
    new_node->parent = old_node->parent;
	new_node->poffset = old_node->pagenum * PAGESZ;
    for (i = 0; i <= new_node->num_keys; i++) {
        child = new_node->pointers[i];
        child->parent = new_node;
		child->poffset = new_node->pagenum * PAGESZ;
		file_write_page(child->pagenum, (page_t*)child);
    }

    /* Insert a new key into the parent of the two
     * nodes resulting from the split, with
     * the old node to the left and the new to the right.
     */

    return insert_into_parent(root, old_node, k_prime, new_node);
}



/* Inserts a new node (leaf or internal node) into the B+ tree.
 * Returns the root of the tree after insertion.
 */
node * insert_into_parent(node * root, node * left, int64_t key, node * right) {

    int left_index;
    node * parent;

    parent = left->parent;

    /* Case: new root. */

    if (parent == NULL)
        return insert_into_new_root(left, key, right);

    /* Case: leaf or node. (Remainder of
     * function body.)  
     */

    /* Find the parent's pointer to the left 
     * node.
     */

    left_index = get_left_index(parent, left);
	file_write_page(left->pagenum, (page_t*)left);
	file_write_page(right->pagenum, (page_t*)right);


    /* Simple case: the new key fits into the node. 
     */

    if (parent->num_keys < INTERNAL_ORDER - 1){
        return insert_into_node(root, parent, left_index, key, right);
	}
    /* Harder case:  split a node in order 
     * to preserve the B+ tree properties.
     */

	// TODO: FROM NOW ON, CONTINUE
    return insert_into_node_after_splitting(root, parent, left_index, key, right);
}


/* Creates a new root for two subtrees
 * and inserts the appropriate key into
 * the new root.
 */
node * insert_into_new_root(node * left, int64_t key, node * right) {

    node * root = make_node(free_page());
    root->keys[0] = key;
    root->pointers[0] = left;
	root->coffset[0] = left->pagenum * PAGESZ;
    root->pointers[1] = right;
	root->coffset[1] = right->pagenum * PAGESZ;
    root->num_keys++;
    root->parent = NULL;
    left->parent = root;
	left->poffset = root->pagenum * PAGESZ;
    right->parent = root;
	right->poffset = root->pagenum * PAGESZ;

	headpg->root = root;
	headpg->roffset = root->pagenum * PAGESZ;

	file_write_page(0, (page_t*)headpg);
	file_write_page(root->pagenum, (page_t*)root);
	file_write_page(left->pagenum, (page_t*)left);
	file_write_page(right->pagenum, (page_t*)right);

    return root;
}



/* First insertion:
 * start a new tree.
 */
node * start_new_tree(int64_t key, record * pointer) {

    node * root = make_leaf(free_page());
    root->keys[0] = key;
    root->pointers[0] = pointer;
    root->pointers[LEAF_ORDER - 1] = NULL;
    root->parent = NULL;
    root->num_keys++;

	headpg->root = root;
	headpg->roffset = root->pagenum * PAGESZ;

	file_write_page(root->pagenum, (page_t*)root);
	file_write_page(0, (page_t*)headpg);

    return root;
}



/* Master insertion function.
 * Inserts a key and an associated value into
 * the B+ tree, causing the tree to be adjusted
 * however necessary to maintain the B+ tree
 * properties.
 */
int insert( int64_t key, char* value ) {
	if(db==NULL){
		fprintf(stderr,"ERROR: No database is selected.\n");
		return FAIL;
	}

	node * root = headpg->root;
    record * pointer;
    node * leaf;

    /* The current implementation ignores
     * duplicates.
     */

    if (find_record(key) != NULL)
        return FAIL;

    /* Create a new record for the
     * value.
     */
    pointer = make_record(value);


    /* Case: the tree does not exist yet.
     * Start a new tree.
     */

    if (root == NULL){
		start_new_tree(key, pointer);
		return SUCCESS;
	}

	/////////////////////

    /* Case: the tree already exists.
     * (Rest of function body.)
     */

    leaf = find_leaf(key);

    /* Case: leaf has room for key and pointer.
     */

    if (leaf->num_keys < LEAF_ORDER - 1) {
        leaf = insert_into_leaf(leaf, key, pointer);
        return SUCCESS;
    }


    /* Case:  leaf must be split.
     */

    insert_into_leaf_after_splitting(root, leaf, key, pointer);
	return SUCCESS;
}




// DELETION.

/* Utility function for deletion.  Retrieves
 * the index of a node's nearest neighbor (sibling)
 * to the left if one exists.  If not (the node
 * is the leftmost child), returns -1 to signify
 * this special case.
 */
int get_neighbor_index( node * n ) {

    int i;

    /* Return the index of the key to the left
     * of the pointer in the parent pointing
     * to n.  
     * If n is the leftmost child, this means
     * return -1.
     */
    for (i = 0; i <= n->parent->num_keys; i++)
        if (n->parent->pointers[i] == n)
            return i - 1;

    // Error state.
    printf("Search for nonexistent pointer to node in parent.\n");
    printf("Node:  %#lx\n", (unsigned long)n);
    exit(EXIT_FAILURE);
}


node * remove_entry_from_node(node * n, int key, void * pointer) {

    int i, num_pointers;

    // Remove the key and shift other keys accordingly.
    i = 0;
    while (n->keys[i] != key)
        i++;
    for (++i; i < n->num_keys; i++)
        n->keys[i - 1] = n->keys[i];

    // Remove the pointer and shift other pointers accordingly.
    // First determine number of pointers.
    num_pointers = n->is_leaf ? n->num_keys : n->num_keys + 1;
    i = 0;
    while (n->pointers[i] != pointer)
        i++;
    for (++i; i < num_pointers; i++){
        n->pointers[i - 1] = n->pointers[i];
		if(!n->is_leaf)
			n->coffset[i - 1] = n->coffset[i];
	}


    // One key fewer.
    n->num_keys--;

    // Set the other pointers to NULL for tidiness.
    // A leaf uses the last pointer to point to the next leaf.
    if (n->is_leaf)
        for (i = n->num_keys; i < LEAF_ORDER - 1; i++)
            n->pointers[i] = NULL;
    else
        for (i = n->num_keys + 1; i < INTERNAL_ORDER; i++){
            n->pointers[i] = NULL;
			n->coffset[i] = 0;
		}

    return n;
}


node * adjust_root(node * root) {

    node * new_root;

    /* Case: nonempty root.
     * Key and pointer have already been deleted,
     * so nothing to be done.
     */

    if (root->num_keys > 0){
		file_write_page(root->pagenum, (page_t*)root);
        return root;
	}

    /* Case: empty root. 
     */

    // If it has a child, promote 
    // the first (only) child
    // as the new root.

    if (!root->is_leaf) {
        new_root = root->pointers[0];
        new_root->parent = NULL;
		new_root->poffset = NO_NODE_PAGE;
		headpg->root = new_root;
		headpg->roffset = new_root->pagenum * PAGESZ;

		file_write_page(new_root->pagenum, (page_t*)new_root); 
		file_write_page(0, (page_t*)headpg);
    }

    // If it is a leaf (has no children),
    // then the whole tree is empty.

    else {
        new_root = NULL;
		headpg->root = NULL;
		headpg->roffset = NO_NODE_PAGE;
		file_write_page(0, (page_t*)headpg);
	}

	file_free_page(root->pagenum);
    free(root->keys);
    free(root->pointers);
    free(root);

    return new_root;
}


/* Coalesces a node that has become
 * too small after deletion
 * with a neighboring node that
 * can accept the additional entries
 * without exceeding the maximum.
 */
node * coalesce_nodes(node * root, node * n, node * neighbor, int neighbor_index, int k_prime) {

    int i, j, neighbor_insertion_index, n_end;
    node * tmp;

    /* Swap neighbor with node if node is on the
     * extreme left and neighbor is to its right.
     */

    if (neighbor_index == -1) {
        tmp = n;
        n = neighbor;
        neighbor = tmp;
    }

    /* Starting point in the neighbor for copying
     * keys and pointers from n.
     * Recall that n and neighbor have swapped places
     * in the special case of n being a leftmost child.
     */

    neighbor_insertion_index = neighbor->num_keys;

    /* Case:  nonleaf node.
     * Append k_prime and the following pointer.
     * Append all pointers and keys from the neighbor.
     */

    if (!n->is_leaf) {

        /* Append k_prime.
         */

        neighbor->keys[neighbor_insertion_index] = k_prime;
        neighbor->num_keys++;


        n_end = n->num_keys;

        for (i = neighbor_insertion_index + 1, j = 0; j < n_end; i++, j++) {
            neighbor->keys[i] = n->keys[j];
            neighbor->pointers[i] = n->pointers[j];
			neighbor->coffset[i] = n->coffset[j];
            neighbor->num_keys++;
            n->num_keys--;
        }

        /* The number of pointers is always
         * one more than the number of keys.
         */

        neighbor->pointers[i] = n->pointers[j];
		neighbor->coffset[i] = n->coffset[j];

        /* All children must now point up to the same parent.
         */

        for (i = 0; i < neighbor->num_keys + 1; i++) {
            tmp = (node *)neighbor->pointers[i];
            tmp->parent = neighbor;
			tmp->poffset = neighbor->pagenum * PAGESZ;
			file_write_page(tmp->pagenum, (page_t*)tmp);
        }
    }

    /* In a leaf, append the keys and pointers of
     * n to the neighbor.
     * Set the neighbor's last pointer to point to
     * what had been n's right neighbor.
     */

    else {
        for (i = neighbor_insertion_index, j = 0; j < n->num_keys; i++, j++) {
            neighbor->keys[i] = n->keys[j];
            neighbor->pointers[i] = n->pointers[j];
            neighbor->num_keys++;
        }
        neighbor->pointers[LEAF_ORDER - 1] = n->pointers[LEAF_ORDER - 1];
		neighbor->rsoffset = n->rsoffset;
    }


	root = delete_entry(root, n->parent, k_prime, n);

	file_write_page(neighbor->pagenum, (page_t*)neighbor);
	file_free_page(n->pagenum);
    free(n->keys);
    free(n->pointers);
    free(n); 
    return root;
}


/* Deletes an entry from the B+ tree.
 * Removes the record and its key and pointer
 * from the leaf, and then makes all appropriate
 * changes to preserve the B+ tree properties.
 */
node * delete_entry( node * root, node * n, int64_t key, void * pointer ) {

    int min_keys;
    node * neighbor;
    int neighbor_index;
    int k_prime_index, k_prime;
    int capacity;

    // Remove key and pointer from node.

    n = remove_entry_from_node(n, key, pointer);

    /* Case:  deletion from the root. 
     */

    if (n == root) 
        return adjust_root(root);


    /* Case:  deletion from a node below the root.
     * (Rest of function body.)
     */

    /* Determine minimum allowable size of node,
     * to be preserved after deletion.
     */

    min_keys = 1;

    /* Case:  node stays at or above minimum.
     * (The simple case.)
     */

    if (n->num_keys >= min_keys){
		file_write_page(n->pagenum, (page_t*)n);
        return root;
	}

    /* Case:  node falls below minimum.
     * Either coalescence or redistribution
     * is needed.
     */

    /* Find the appropriate neighbor node with which
     * to coalesce.
     * Also find the key (k_prime) in the parent
     * between the pointer to node n and the pointer
     * to the neighbor.
     */

    neighbor_index = get_neighbor_index( n );
    k_prime_index = neighbor_index == -1 ? 0 : neighbor_index;
    k_prime = n->parent->keys[k_prime_index];
    neighbor = neighbor_index == -1 ? n->parent->pointers[1] : 
        n->parent->pointers[neighbor_index];

    /* Coalescence. delay_merge */
	// FIXME: MERGE!
    return coalesce_nodes(root, n, neighbor, neighbor_index, k_prime);

}



/* Master deletion function.
 */
int delete(int64_t key) {
	if(db==NULL){
		fprintf(stderr,"ERROR: No database is selected.\n");
		return FAIL;
	}

	node * root;
    node * key_leaf;
    record * key_record;

	root = headpg->root;
    key_record = find_record(key);
    key_leaf = find_leaf(key);
    if (key_record != NULL && key_leaf != NULL) {
        root = delete_entry(root, key_leaf, key, key_record);
        free(key_record);
    }
    return SUCCESS;
}


/* Utilities */

int pathname_check(char* pathname){

	if(pathname==NULL || pathname[0]=='\0'){
		fprintf(stderr,"ERROR: \"pathname\" is wrong."
				" Input a correct pathname.\n");
		return FAIL;
	} else {
		return SUCCESS;
	}
}


// caution: The file pointer moves to SEEK_END
uint64_t get_file_size(){
	fseek(db, 0, SEEK_END);
	return ftell(db);
}

char* mem_make_write_buf(const page_t* pg){
	if(pg == NULL){
		fprintf(stderr,"ERROR: pg is NULL."
				" (in mem_make_buf)\n");
		return NULL;
	}

	char* buf;

	buf=malloc(PAGESZ);
	if(buf == NULL){
		fprintf(stderr,"ERROR: Malloc of buf failed."
				" (in mem_make_buf)\n");
		return NULL;
	}
	memset(buf,0,PAGESZ);

	switch(pg->type){

		case HEADER:{
			header_page_t* hpg=(header_page_t*)pg;
			memcpy(buf, &(hpg->foffset), 8);
			memcpy(buf+8, &(hpg->roffset), 8);
			memcpy(buf+16, &(hpg->num_pages), 8);
			// 24~PAGESZ: Reserved
			break;
		}
		case FREE:{
			free_page_t* fpg=(free_page_t*)pg;
			memcpy(buf, &(fpg->nfoffset), 8);
			// 8~PAGESZ: Not used
			break;
		}
		case LEAF:{
			node* lpg=(node*)pg;
			// START ... Leaf Page Header
			memcpy(buf, &(lpg->poffset), 8);
			memcpy(buf+8, &(lpg->is_leaf), 4);
			memcpy(buf+12, &(lpg->num_keys), 4);
			// 16~120: Reserved
			memcpy(buf+120, &(lpg->rsoffset), 8);
			// END ... Leaf Page Header
			for(int i=0; i < lpg->num_keys; i++){
				memcpy(buf+128*(i+1), &(lpg->keys[i]), 8);
				memcpy(buf+128*(i+1)+8, 
						((record*)lpg->pointers[i])->value,
						120);
			}
			break;
		}
		case INTERNAL:{
			node* ipg=(node*)pg;
			// START ... Leaf Page Header
			memcpy(buf, &(ipg->poffset), 8);
			memcpy(buf+8, &(ipg->is_leaf), 4);
			memcpy(buf+12, &(ipg->num_keys), 4);
			// 16_120: Reserved
			memcpy(buf+120, &(ipg->coffset[0]), 8);
			// END ... Leaf Page Header
			for(int i=1; i <= ipg->num_keys; i++){
				memcpy(buf+128+16*i, &(ipg->keys[i-1]), 8);
				memcpy(buf+128+16*i+8, &(ipg->coffset[i]), 8);
			}
			break;
		}
		default:{
			fprintf(stderr,"ERROR: The type of the page "
					"is not determined. (in mem_make_buf)\n");
			return NULL;
		}
	}

	return buf;
}

char* mem_make_read_buf(){
	
	char* buf;

	buf = malloc(PAGESZ);

	if(buf == NULL){
		fprintf(stderr,"ERROR: Malloc of buf failed."
				" (in mem_make_buf)\n");
		return NULL;
	}
	memset(buf,0,PAGESZ);

	return buf;
}

void mem_dealloc_buf(char* buf){
	if(buf == NULL){
		fprintf(stderr, "ERROR: buf is not allocated."
				" (in mem_dealloc_buf)\n");
	} else {
		free(buf);
	}
}


header_page_t* mem_make_header_page(){

	headpg = malloc(sizeof(header_page_t));
	if(headpg==NULL){
		fprintf(stderr,"ERROR: Malloc of headpg failed. "
				"(in mem_make_header_page)\n");
		return NULL;
	}

	headpg->type = HEADER;
	headpg->pagenum = 0;
	headpg->foffset = NO_FREE_PAGE;
	headpg->free = NULL;
	headpg->roffset = NO_NODE_PAGE;
	headpg->root = NULL;
	headpg->num_pages = 1;

	return headpg;
}

void mem_dealloc_header_page(){

	if(headpg==NULL){
		fprintf(stderr,"ERROR: headpg is not allocated."
				" (in mem_free_header_page)\n");
	} else{
		free(headpg);
		headpg=NULL;
	}
}

pagenum_t file_alloc_header_page(){
	
	assert(headpg == NULL);

	if(mem_make_header_page() == NULL){
		return FAIL;	// TODO: Handling
	}

	file_write_page(0, (page_t*)headpg);

	return 0;
}

free_page_t* mem_make_free_page(pagenum_t pagenum){

	free_page_t* freepg;
	freepg = malloc(sizeof(free_page_t));
	if(free == NULL){
		fprintf(stderr, "ERROR: Malloc of freepg failed."
				" (in mem_make_free_page)\n");
		return NULL;
	}

	freepg->type = FREE;
	freepg->pagenum = pagenum;
	freepg->nfoffset = 0;
	freepg->next = NULL;

	return freepg;
}

void mem_dealloc_free_page(free_page_t* free_page){
	if(free_page == NULL){
		fprintf(stderr,"ERROR: free_page is not allocated."
				" (in mem_dealloc_free_page)\n");
	} else {
		free(free_page);
	}
}

pagenum_t file_alloc_free_page(pagenum_t new_pagenum){
	assert(headpg != NULL);

	free_page_t* new_page;

	new_page = mem_make_free_page(new_pagenum);
	if(new_page == NULL){
		return FAIL;	// TODO: Handling
	}

	new_page->nfoffset = headpg->foffset;
	new_page->next = headpg->free;

	headpg->foffset = new_pagenum*PAGESZ;
	headpg->free = new_page;
	headpg->num_pages++;

	file_write_page(0, (page_t*)headpg);
	file_write_page(new_pagenum, (page_t*)new_page);
	
	return new_pagenum;
}

int mem_read_page(char* buf, page_t* dest){

	if(buf == NULL){
		fprintf(stderr, "buf is NULL."
				" (in mem_read_page)\n");
		return FAIL;
	}
	if(dest == NULL){
		fprintf(stderr, "dest is NULL."
				" (in mem_read_page)\n");
		return FAIL;
	}

	switch(dest->type){

		case HEADER:{
			header_page_t* hpg = (header_page_t*)dest;
			memcpy(&(hpg->foffset), buf, 8);
			memcpy(&(hpg->roffset), buf+8, 8);
			memcpy(&(hpg->num_pages), buf+16, 8);
			break;
		}
		case FREE:{
			free_page_t* fpg = (free_page_t*)dest;
			memcpy(&(fpg->nfoffset), buf, 8);
			break;
		}
		case LEAF:{
			node* lpg = (node*)dest;
			char value[120] = { 0,};
			memcpy(&(lpg->poffset), buf, 8);
			memcpy(&(lpg->is_leaf), buf+8, 4);
			memcpy(&(lpg->num_keys), buf+12, 4);
			memcpy(&(lpg->rsoffset), buf+120, 8);
			for(int i=0; i < lpg->num_keys; i++){
				memcpy(&(lpg->keys[i]), buf+128*(i+1), 8);	
				memcpy(value, buf+128*(i+1)+8, 120);
				lpg->pointers[i] = (void*)make_record(value);
			}
			break;
		}
		case INTERNAL:{
			node* ipg=(node*)dest;
			memcpy(&(ipg->poffset), buf, 8);
			memcpy(&(ipg->is_leaf), buf+8, 4);
			memcpy(&(ipg->num_keys), buf+12, 4);
			memcpy(&(ipg->coffset[0]), buf+120, 8);
			for(int i=1; i <= ipg->num_keys; i++){
				memcpy(&(ipg->keys[i-1]), buf+128+16*i, 8);
				memcpy(&(ipg->coffset[i]), buf+128+16*i+8, 8);
			}
			break;
		}
		default:{
			fprintf(stderr,"ERROR: The type of the page "
					"is not determined. (in mem_read_page)\n");
			return FAIL;
		}
	}

	return SUCCESS;
}

/* file managing */
pagenum_t file_alloc_page(){
	assert(db!=NULL);
	
	pagenum_t pgnum;
	
	pgnum = get_file_size() / PAGESZ;

	if(pgnum == 0){

		assert(headpg==NULL);

		file_alloc_header_page();


	} else {	// The database has the header page.
		
		assert(headpg!=NULL);

		file_alloc_free_page(pgnum);

	}

	return pgnum;
}

void file_free_page(pagenum_t pagenum){
	assert(db!=NULL && headpg!=NULL);

	free_page_t* free_page = mem_make_free_page(pagenum);

	free_page->nfoffset = headpg->foffset;
	free_page->next = headpg->free;

	headpg->foffset = pagenum * PAGESZ;
	headpg->free = free_page;
	/* if(page to free == root page) handle in caller. */

	file_write_page(pagenum, (page_t*)free_page);
	file_write_page(0, (page_t*)headpg);
}

void file_read_page(pagenum_t pagenum, page_t* dest){
	assert(db!=NULL);

	if(dest == NULL){
		fprintf(stderr, "ERROR: dest is NULL."
				" (in file_read_page)\n");
		return;
	}

	dest->pagenum = pagenum;

	char* buf;
	buf = mem_make_read_buf();
	if(buf == NULL){
		/* TODO: handling */
		return;
	}
	
	fseek(db, pagenum * PAGESZ, SEEK_SET);

	if(fread(buf, PAGESZ, 1, db) < 0){
		fprintf(stderr, "ERROR: fread failed."
				" (in file_read_page)\n");
		// TODO: handling 
		mem_dealloc_buf(buf);
		return;
	}

	if(mem_read_page(buf, dest) < 0){
		// TODO: handling
		mem_dealloc_buf(buf);
		return;
	}

	mem_dealloc_buf(buf);

}

void file_write_page(pagenum_t pagenum, const page_t* src){
	assert(db!=NULL);

	if(src == NULL){
		fprintf(stderr, "ERROR: src is NULL."
				" (in file_write_page)\n");
		return;
	}

	char* buf;

	buf = mem_make_write_buf(src);
	if(buf == NULL){
		/* TODO: handling */
		return;
	}

	fseek(db, pagenum*PAGESZ, SEEK_SET);

	if(fwrite(buf, PAGESZ, 1, db) < 0){
		fprintf(stderr, "ERROR: fwrite failed."
				" (in file_write_page)\n");
		// TODO: handling
	}

	mem_dealloc_buf(buf);
}


/* API services */

// 1. open

void create_db(){
	for(int i = 0; i< DEFAULT_NUMBER_OF_PAGES; i++){
		file_alloc_page();
	}
}

int open_header_page(){

	if(mem_make_header_page() == NULL){
		// TODO: handling
		return FAIL;
	}
	file_read_page(0, (page_t*)headpg);

	return SUCCESS;
}

int open_free_pages(){
	free_page_t *before, *after;
	uint64_t foffset;

	if(headpg->foffset != NO_FREE_PAGE){
		after = mem_make_free_page((headpg->foffset)/PAGESZ);
		if(after == NULL){
			// TODO: handling: HEADER
			return FAIL;
		}
		file_read_page(after->pagenum, (page_t*)after);
		headpg->free = after;

		for(before = after; before->nfoffset != NO_FREE_PAGE;
				before = after){

			after = mem_make_free_page((before->nfoffset)/PAGESZ);
			if(after == NULL){
				// TODO: handling: HEADER, FREE
				return FAIL;
			}

			file_read_page(after->pagenum, (page_t*)after);
			before->next = after;
		}
	}

	return SUCCESS;
}

node* open_node(pagenum_t pagenum){

	if(pagenum == NO_NODE_PAGE) return NULL;

	int is_leaf;
	free_page_t* temp;
	node* node;
	char* buf;
	
	temp = mem_make_free_page(pagenum);
	buf = mem_make_read_buf();
	fseek(db, pagenum * PAGESZ, SEEK_SET);
	fread(buf, PAGESZ, 1, db);
	memcpy(&is_leaf, buf + 8, 4);
	mem_dealloc_buf(buf);

	if(is_leaf == 1){
		node = make_leaf(temp);
	} else if(is_leaf == 0){
		node = make_node(temp);
	} else {
		fprintf(stderr,"ERROR: wrong type of is_leaf"
				" (in open_nodes)\n");
		//TODO: handling, to check
		return NULL;
	}

	file_read_page(pagenum, (page_t*)node);	

	return node;
}

node* open_root(){
	node* root = open_node(headpg->roffset / PAGESZ);
	headpg -> root = root;
	return root;
}

node* build_nodes(node* root, node* sibling[2]){

	int i;
	if (!root->is_leaf) {
		for (i = 0; i < root->num_keys + 1; i++){
			node* child = open_node(root->coffset[i] / PAGESZ);
			root->pointers[i] = child;
			child->parent = root;
			build_nodes(child,sibling);
		}
	} else {
		sibling[1] = root;
		if(sibling[0] != NULL){
			sibling[0]->pointers[LEAF_ORDER-1] = (void*)sibling[1];
			
		}
		sibling[0] = sibling[1];
	}

	return root;
}

int open_db_entry(){

	if(open_header_page() < 0){
		// TODO: handling
		return FAIL;
	}
	if(open_free_pages() < 0){
		// TODO: handling
		return FAIL;
	}

	/* TODO: FROM NOW ON, CONTINUE AGAIN */
	node* root;
	root = open_root();
	if(root != NULL){
		node* sibling[2] = { NULL, NULL };
		build_nodes(root,sibling);
		
	} /* else: no root page */

	return SUCCESS;
}

int open_db(char* pathname){
	if(pathname_check(pathname) < 0){
		return FAIL;
	}

	uint64_t fsz;	// file size

	db = fopen(pathname, "r+b");
	if(db == NULL){	// There is no file named $pathname.
		db = fopen(pathname, "a+b");	// == "touch $pathname"
		fclose(db);
		db = fopen(pathname, "r+b");

		create_db();

	} else {	// The file named $pathname exists.
		open_db_entry();
	}
	
	assert(db != NULL);

	return SUCCESS;
}

