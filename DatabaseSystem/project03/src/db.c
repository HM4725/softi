#include "bpt_internal.h"
#include "panic.h"
#include "buffer.h"

int init_bufmgr(int buf_num){
	bufmgr.first_buf = NULL;
	bufmgr.num_pages = 0;
	bufmgr.capacity = buf_num;

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
	}

	td.num_alloc_tables = 0;
	td.capacity = TABLE_MAX_ID;

	return SUCCESS;
}

int init_bufmgr_and_table_directory(int buf_num) {
	init_bufmgr(buf_num);
	init_table_directory();
	return SUCCESS;
}


int find_vacant_table_id() {
	int tid;
	Table* table = td.tables;

	if (td.num_alloc_tables == td.capacity) {
		printf("Table directory is full.\n");
		return FAIL;
	}

	for (tid = 1; tid <= TABLE_MAX_ID; tid++) {
		if (table[tid].fd == NOTOPEN)
			break;
	}
	return tid;
}

// Opens a table file or creates a new file if not exist.
int open_or_create_table_file(const char* filename) {
	int tid;
	int fd;
	HeaderPage* new_header;
	char* new_name;
	Table* table;

	if ((tid = find_vacant_table_id()) == FAIL) {
		return FAIL;
	}
	table = &td.tables[tid];

    fd = open(filename, O_RDWR);
    if (fd < 0) {
        // Creates a new table file
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
        new_header->pagenum = 0;
		table->fd = fd;
        file_write_page(tid, (Page*)new_header);
    } else {
        // Table file exists. Loads header info
		new_header = (HeaderPage*)malloc(sizeof(HeaderPage));
		if (new_header == NULL) {
			PANIC("failed to allocate new header");
		}
		memset(new_header, 0, PAGE_SIZE);
		table->fd = fd;
        file_read_page(tid, 0, (Page*)new_header);
        new_header->pagenum = 0;
    }
	
	new_name = (char*)malloc(sizeof(char) * (FILENAME_MAX_LENGTH + 1) );
	memset(new_name, 0, FILENAME_MAX_LENGTH + 1);
	strncpy(new_name, filename, FILENAME_MAX_LENGTH);

	table->header = new_header;
	table->name = new_name; 
	td.num_alloc_tables ++;

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
			if(delete_buf(buf) < 0) {
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
		td.num_alloc_tables--;
	} else {
		fprintf(stderr, "some buffer blocks for \"%s\" table are still being used.\n", table->name);
	}
}

int destroy_bufmgr(){
	Buf* buf;

	for(buf = bufmgr.first_buf; buf != NULL; buf = buf->next){
		if(buf->is_dirty)
			update_file(buf);
	}

	return SUCCESS;
}
