#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <sys/types.h>
#include "table.h"
#include "file.h"

// Use Buffer Management
#define BUFFER

/* DATA STRUCTURE */

typedef uint64_t pagenum_t;
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
	Buf* free_buf;
	int capacity;
};


/* GLOBAL */
extern BufMgr bufmgr;

/* FUNCTION PROTOTYPES */
Buf* buf_search(int table_id, pagenum_t pagenum);
void hash_insert(int table_id, pagenum_t key, Buf* val);
void hash_delete(int table_id, pagenum_t key);
void buf_make_free();
Buf* buf_get_free();
int buf_release(Buf* buf);
Buf* buf_find_lru();
void buf_overwrite(Buf* buf, int table_id, pagenum_t pagenum);
Buf* buf_alloc(int table_id, pagenum_t pagenum);
void buf_sync_file(Buf* buf);
void buf_move_to_first(Buf* buf);
void buf_read_page(Buf* buf, Page* page);
void buf_write_page(Buf* buf, const Page* page);


#endif // __BUFFER_H__
