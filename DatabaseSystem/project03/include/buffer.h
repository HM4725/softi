#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <sys/types.h>
#include "file.h"

// If is_dirty == WRITE_TERM, write the page on disk
#define WRITE_TERM 1000
// Use Buffer Management
#define BUFFER

/* DATA STRUCTURE */

typedef struct _Buf Buf;
typedef struct _BufMgr BufMgr;

struct _Buf {
	char frame[PAGE_SIZE];
	int table_id;
	pagenum_t pagenum;
	int is_dirty;
	int is_pinned;
	// Used for LRU policy.
	Buf* prev;
	Buf* next;
};

struct _BufMgr {
	Buf* first_buf;
	int num_pages;
	int capacity;
};


/* GLOBAL */
extern BufMgr bufmgr;

/* FUNCTION PROTOTYPES */
Buf* find_buf(int table_id, pagenum_t pagenum);
Buf* insert_buf(int table_id, pagenum_t pagenum);
int delete_buf(Buf* buf);
void update_file(Buf* buf);
void buf_read_page(Buf* buf, Page* page);
void buf_write_page(Buf* buf, Page* page);


#endif // __BUFFER_H__
