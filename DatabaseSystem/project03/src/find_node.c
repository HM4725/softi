#include "bpt_internal.h"

/* Traces the path from the root to a leaf, searching
 * by key.  Displays information about the path
 * if the verbose flag is set.
 * Returns the leaf containing the given key.
 */
bool find_leaf(int table_id, uint64_t key, LeafPage* out_leaf_node) {
    int i = 0;
	HeaderPage* header = td.tables[table_id].header;
    off_t root_offset = header->root_offset;

	if (root_offset == 0) {
		return false;
	}
    
    NodePage page;
    file_read_page(table_id, FILEOFF_TO_PAGENUM(root_offset), (Page*)&page);

	while (!page.is_leaf) {
        InternalPage* internal_node = (InternalPage*)&page;

        i = 0;
		while (i < internal_node->num_keys) {
			if (key >= INTERNAL_KEY(internal_node, i)) i++;
			else break;
		}
        
        file_read_page(table_id, FILEOFF_TO_PAGENUM(INTERNAL_OFFSET(internal_node, i)),
                       (Page*)&page);
	}

    memcpy(out_leaf_node, &page, sizeof(LeafPage));

	return true;
}

/* Finds and returns the value to which
 * a key refers.
 */
char* find_record(int table_id, uint64_t key) {
	if(table_id < 1 || table_id > td.capacity) {
		fprintf(stderr, "table id %d is out of range.\n", table_id);
		return NULL;
	}
	if(table_id < 1 || td.tables[table_id].fd == NOTOPEN) {
		fprintf(stderr, "The table of id[%d] is not open yet.\n", table_id);
		return NULL;
	}

    int i = 0;
    char* out_value;

    LeafPage leaf_node;
    if (!find_leaf(table_id, key, &leaf_node)) {
        return NULL;
    }

	for (i = 0; i < leaf_node.num_keys; i++) {
		if (LEAF_KEY(&leaf_node, i) == key) {
            out_value = (char*)malloc(SIZE_VALUE * sizeof(char));
            memcpy(out_value, LEAF_VALUE(&leaf_node, i), SIZE_VALUE);
            return out_value;
        }
    }

    return NULL;
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
