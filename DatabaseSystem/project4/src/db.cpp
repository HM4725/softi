#include "bpt_internal.h"
#include "panic.h"
#include "buffer.h"

int init_bufmgr(int buf_num){
	bufmgr.first_buf = NULL;
	bufmgr.capacity = buf_num;
	for(int i = 0; i < buf_num ; i++) {
		buf_make_free();
	}

	return SUCCESS;
}

int init_table_directory() {
	int i = 0;
	Table* table = td.tables;

	table[0].fd = DISUSED;
	table[0].name = DISUSED;
	table[0].header = DISUSED;

	for(i = 1; i <= TABLE_MAX_ID; i++) {
		table[i].fd = NOTOPEN;
		table[i].header = NULL;
		table[i].name = NULL;
		table[i].hash_table = NULL;
		table[i].hash_size = 0;
	}

	td.num_open_tables = 0;
	td.capacity = TABLE_MAX_ID;

	return SUCCESS;
}

int init_bufmgr_and_table_directory(int buf_num) {
	init_bufmgr(buf_num);
	init_table_directory();
	return SUCCESS;
}

int get_vacant_table_id() {
	int tid;
	Table* table = td.tables;

	if (td.num_open_tables == td.capacity) {
		printf("Table directory is full.\n");
		return FAIL;
	}

	for (tid = 1; tid <= TABLE_MAX_ID; tid++) {
		if (table[tid].fd == NOTOPEN)
			break;
	}
	return tid;
}

uint64_t get_num_records(int table_id) {
	Table* table = &td.tables[table_id];
	off_t root_offset = table->header->root_offset;
	int num_records = 0;
	InternalPage* internal_node;
	LeafPage* leaf_node;
	NodePage page;

	if(root_offset == 0) {
		return 0;
	}

	file_read_page(table_id, FILEOFF_TO_PAGENUM(root_offset), (Page*)&page);

	while(!page.is_leaf) {
		internal_node = (InternalPage*)&page;

		file_read_page(table_id, FILEOFF_TO_PAGENUM(INTERNAL_OFFSET(internal_node, 0)),
				(Page*)&page);
	}

	leaf_node = (LeafPage*)&page;
	while(true) {
		num_records += leaf_node->num_keys;
		if(leaf_node->sibling == 0) {
			break;
		}
		file_read_page(table_id, FILEOFF_TO_PAGENUM(leaf_node->sibling), (Page*)&page);
	}

	return num_records;
}

// Opens a table file or creates a new file if not exist.
int open_or_create_table_file(char* filename, int num_columns) {
	int tid;
	int fd;
	pagenum_t num_pages;
	HeaderPage* new_header;
	char* new_name;
	Table* table;

	if ((tid = get_vacant_table_id()) == FAIL) {
		return FAIL;
	}
	table = &td.tables[tid];

    fd = open(filename, O_RDWR);
    if (fd < 0) {
        // Creates a new table file
		if(num_columns < 2 || num_columns > 16) {
			fprintf(stderr, "Constraint: 2 <= num_columns <= 16\n");
			return FAIL;
		}

        fd = open(filename, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
        if (fd < 0) {
            PANIC("failed to create new db file");
        }

		new_header = (HeaderPage*)malloc(sizeof(HeaderPage));
		if (new_header == NULL) {
			PANIC("failed to allocate new header");
		}
        memset(new_header, 0, PAGE_SIZE);
        new_header->freelist = 0;
        new_header->root_offset = 0;
        new_header->num_pages = 1;
		new_header->num_columns = num_columns;
        new_header->pagenum = 0;
		table->fd = fd;

		table->hash_table = (Buf**)malloc(sizeof(Buf*));
		if(table->hash_table == NULL) {
			PANIC("failed to allocate a hash table");
		}
		memset(table->hash_table, 0, sizeof(Buf*));
		table->hash_size = 1;

        file_write_page(tid, (Page*)new_header);

    } else {
        // Table file exists. Loads header info
		new_header = (HeaderPage*)malloc(sizeof(HeaderPage));
		if (new_header == NULL) {
			PANIC("failed to allocate new header");
		}
		memset(new_header, 0, PAGE_SIZE);
		table->fd = fd;

		num_pages = FILEOFF_TO_PAGENUM(lseek(fd, 0, SEEK_END));
		table->hash_table = (Buf**)malloc(sizeof(Buf*) * num_pages);
		if(table->hash_table == NULL) {
			PANIC("failed to allocate a hash table");
		}
		memset(table->hash_table, 0, sizeof(Buf*) * num_pages);
		table->hash_size = num_pages;

        file_read_page(tid, 0, (Page*)new_header);
        new_header->pagenum = 0;
    }
	
	new_name = (char*)malloc(sizeof(char) * (FILENAME_MAX_LENGTH + 1) );
	memset(new_name, 0, FILENAME_MAX_LENGTH + 1);
	strncpy(new_name, filename, FILENAME_MAX_LENGTH);

	table->header = new_header;
	table->name = new_name;
	table->num_records = get_num_records(tid);
	td.num_open_tables ++;
	

    return SUCCESS;
}

int find_table_id(char* filename) {
	char* tname;
	for(int i = 1; i <= td.capacity; i++) {
		tname = td.tables[i].name;
		if(tname != NULL && strcmp(tname, filename) == 0) {
			return i;
		}
	}
	fprintf(stderr, "There is no table named \"%s\"\n", filename);
	return FAIL;
}

// Closes the table file.
void close_table_file(int table_id) {
	if(table_id < 1 || table_id > td.capacity) {
		fprintf(stderr, "table id %d is out of range.\n", table_id);
		return;
	}
	if(table_id < 1 || td.tables[table_id].fd == NOTOPEN) {
		fprintf(stderr, "The table of id[%d] is not open yet.\n", table_id);
		return;
	}

	Buf* buf;
	Buf* next;
	Table* table;
	int all_closed;

	buf = bufmgr.first_buf;
	table = &td.tables[table_id];
	all_closed = true;

	while(buf != NULL) {
		next = buf->next;
		if(buf->table_id == table_id) {
			if(buf_release(buf) < 0) {
				all_closed = false;
			}
		}
		buf = next;
	}
	
	if(all_closed) {
		close(table->fd);
		table->fd = NOTOPEN;
		free(table->header);
		table->header = NULL;
		free(table->name);
		table->name = NULL;
		free(table->hash_table);
		table->hash_table = NULL;
		table->hash_size = 0;
		td.num_open_tables--;
	} else {
		fprintf(stderr, "some buffer blocks for \"%s\" table are still being used.\n", table->name);
	}
}

int destroy_bufmgr(){
	Buf* buf;

	for(buf = bufmgr.first_buf; buf != NULL; buf = buf->next){
		buf_sync_file(buf);
	}

	return SUCCESS;
}
