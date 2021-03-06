#include "bpt_internal.h"

// Initialize buffer pool with given number and buffer manager.
int init_db(int buf_num){
	return init_bufmgr_and_table_directory(buf_num);
}

// Opens a table file. Creates a file if not exist.
int open_table(const char* filename) {
    return open_or_create_table_file(filename);
}

// Closes the table file.
void close_table(int table_id) {
    close_table_file(table_id);
}

// Shutdown db by destroying the buffer manager.
int shutdown_db() {
	return destroy_bufmgr();
}

/* Inserts a new record.
 */
int insert(int table_id, uint64_t key, const char* value) {
    return insert_record(table_id, key, value);
}

/* Deletes a record.
 */
int delete(int table_id, uint64_t key) {
    return delete_record(table_id, key);
}

/* Finds a value from key in the b+ tree.
 */
char* find(int table_id, uint64_t key) {
    return find_record(table_id, key);
}

/* Prints the B+ tree in the command
 * line in level (rank) order, with the 
 * keys in each node and the '|' symbol
 * to separate nodes.
 * With the verbose_output flag set.
 * the values of the pointers corresponding
 * to the keys also appear next to their respective
 * keys, in hexadecimal notation.
 */
void print_tree(int table_id) {
	HeaderPage* header = td.tables[table_id].header;
    off_t *queue;
    int i;
    int front = 0;
    int rear = 0;


    if (header->root_offset == 0) {
		printf("Empty tree.\n");
        return;
    }
    queue = (off_t*)malloc(sizeof(off_t) * BPTREE_MAX_NODE);

    queue[rear] = header->root_offset;
    rear++;
    queue[rear] = 0;
    rear++;
    while (front < rear) {
        off_t page_offset = queue[front];
        front++;

        if (page_offset == 0) {
            printf("\n");
            
            if (front == rear) break;

            // next tree level
            queue[rear] = 0;
            rear++;
            continue;
        }
        
        NodePage node_page;
        file_read_page(table_id, FILEOFF_TO_PAGENUM(page_offset), (Page*)&node_page);
        if (node_page.is_leaf == 1) {
            // leaf node
            LeafPage* leaf_node = (LeafPage*)&node_page;
            for (i = 0; i < leaf_node->num_keys; i++) {
                printf("%" PRIu64 " ", LEAF_KEY(leaf_node, i));
            }
            printf("| ");
        } else {
            // internal node
            InternalPage* internal_node = (InternalPage*)&node_page;
            for (i = 0; i < internal_node->num_keys; i++) {
                printf("%" PRIu64 " ", INTERNAL_KEY(internal_node, i));
                queue[rear] = INTERNAL_OFFSET(internal_node, i);
                rear++;
            }
            queue[rear] = INTERNAL_OFFSET(internal_node, i);
            rear++;
            printf("| ");
        }
    }
    free(queue);
}

/* Finds the record under a given key and prints an
 * appropriate message to stdout.
 */
void find_and_print(int table_id, uint64_t key) {
    char* value_found = NULL;
	value_found = find(table_id, key);
	if (value_found == NULL) {
		printf("Record not found under key %" PRIu64 ".\n", key);
    }
	else {
		printf("key %" PRIu64 ", value [%s].\n", key, value_found);
        free(value_found);
    }
}

/* Copyright and license notice to user at startup. 
 */
void license_notice( void ) {
	printf("bpt version %s -- Copyright (C) 2010  Amittai Aviram "
			"http://www.amittai.com\n", Version);
	printf("This program comes with ABSOLUTELY NO WARRANTY; for details "
			"type `show w'.\n"
			"This is free software, and you are welcome to redistribute it\n"
			"under certain conditions; type `show c' for details.\n\n");
}

/* Routine to print portion of GPL license to stdout.
 */
void print_license( int license_part ) {
	int start, end, line;
	FILE * fp;
	char buffer[0x100];

	switch(license_part) {
	case LICENSE_WARRANTEE:
		start = LICENSE_WARRANTEE_START;
		end = LICENSE_WARRANTEE_END;
		break;
	case LICENSE_CONDITIONS:
		start = LICENSE_CONDITIONS_START;
		end = LICENSE_CONDITIONS_END;
		break;
	default:
		return;
	}

	fp = fopen(LICENSE_FILE, "r");
	if (fp == NULL) {
		perror("print_license: fopen");
		exit(EXIT_FAILURE);
	}
	for (line = 0; line < start; line++)
		fgets(buffer, sizeof(buffer), fp);
	for ( ; line < end; line++) {
		fgets(buffer, sizeof(buffer), fp);
		printf("%s", buffer);
	}
	fclose(fp);
}

/* First message to the user.
 */
void usage_1( void ) {
	printf("B+ Tree of Order %d(Internal).\n", order_internal);
    printf("Following Silberschatz, Korth, Sidarshan, Database Concepts, "
           "5th ed.\n\n");
}

/* Second message to the user.
 */
void usage_2( void ) {
	printf("Enter any of the following commands after the prompt > :\n"
	"\to <t>  -- Open the table named <t>.\n"
	"\tc <t>  -- Close the table named <t>.\n"
	"\ti <t> <k> <v>  -- Insert <k> (an integer) as key and <v> (CHAR(120)) to <t> (table name).\n"
	"\tf <t> <k>  -- Find the value under key <k> of the table <t>.\n"
	"\tp <t> <k> -- Same with f <t> <k>.\n"
	"\td <t> <k>  -- Delete key <k> and its associated value of the table <t>.\n"
	"\tt <t> -- Print the B+ tree of the table <t>.\n"
	"\tq -- Quit. (Or use Ctl-D.)\n"
	"\t? -- Print this help message.\n");
}

