#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "file.h"
#include "panic.h"
#include "buffer.h"

// Expands file pages and prepends them to the free list
void expand_file(int table_id, size_t cnt_page_to_expand) {
	HeaderPage* header;
	int fd;
    off_t offset;

	header = td.tables[table_id].header;
	fd = td.tables[table_id].fd;
	offset = header->num_pages * PAGE_SIZE;
    
    int i;
    for (i = 0; i < cnt_page_to_expand; i++) {
        file_free_page(table_id, FILEOFF_TO_PAGENUM(offset));
        header->num_pages++;
        offset += PAGE_SIZE;
    }

    file_write_page(table_id, (Page*)header);
}

// Gets a free page to use.
// If there is no more free pages, expands the db file.
pagenum_t file_alloc_page(int table_id) {
	HeaderPage* header;
	int fd;
    off_t freepage_offset;
    
	header = td.tables[table_id].header;
	fd = td.tables[table_id].fd;
    freepage_offset = header->freelist;
    if (freepage_offset == 0) {
        // No more free pages, expands the db file as twice
        expand_file(table_id, header->num_pages);
        freepage_offset = header->freelist;
    }
   
    FreePage freepage;

	lseek(fd, freepage_offset, SEEK_SET);
	read(fd, &freepage, PAGE_SIZE);
	freepage.pagenum = FILEOFF_TO_PAGENUM(freepage_offset);

	header->freelist = freepage.next;
    
    file_write_page(table_id, (Page*)header);

    return FILEOFF_TO_PAGENUM(freepage_offset);
}

// Puts free page to the free list
void file_free_page(int table_id, pagenum_t pagenum) {
	HeaderPage* header;
	int fd;
	Buf* buf;
    FreePage freepage;
    memset(&freepage, 0, PAGE_SIZE);

	header = td.tables[table_id].header;
	fd = td.tables[table_id].fd;

    freepage.next = header->freelist;
    freepage.pagenum = pagenum;

	// When free the page on the buffer pool, delete the buffer block.
	buf = find_buf(table_id, pagenum);
	if(buf != NULL) {
		delete_buf(buf);
	}
 
    lseek(fd, PAGENUM_TO_FILEOFF(pagenum), SEEK_SET);
    write(fd, &freepage, PAGE_SIZE);

    header->freelist = PAGENUM_TO_FILEOFF(pagenum);

    file_write_page(table_id, (Page*)header);
}

void file_read_page(int table_id, pagenum_t pagenum, Page* page) {
#ifdef BUFFER
	Buf* buf;
	Buf* lru_buf;

	buf = find_buf(table_id, pagenum);

	if (buf != NULL) { // cache hit
		buf_read_page(buf, page);
	} else {	// cache miss
		if (bufmgr.num_pages >= bufmgr.capacity) {
			lru_buf = bufmgr.first_buf->prev;
			while(delete_buf(lru_buf) < 0) {
				lru_buf = lru_buf->prev;
			}
		}
		buf = insert_buf(table_id, pagenum);
		if(buf == NULL) return;
		buf_read_page(buf, page);
	}
#else
	lseek(td.tables[table_id].fd, PAGENUM_TO_FILEOFF(pagenum), SEEK_SET);
	read(td.tables[table_id].fd, page, PAGE_SIZE);
	page->pagenum = pagenum;
#endif
}

void file_write_page(int table_id, Page* page) {
#ifdef BUFFER
	pagenum_t pagenum;
	Buf* buf;
	Buf* lru_buf;

	pagenum = page->pagenum;
	buf = find_buf(table_id, pagenum);

	if (buf != NULL) { // cache hit
		buf_write_page(buf, page);
		if(buf->is_dirty == WRITE_TERM) {
			update_file(buf);
			buf->is_dirty = 0;
		}
	} else {	// cache miss
		if (bufmgr.num_pages >= bufmgr.capacity) {
			lru_buf = bufmgr.first_buf->prev;
			while(delete_buf(lru_buf) < 0) {
				lru_buf = lru_buf->prev;
			}
		}
		buf = insert_buf(table_id, pagenum);
		if(buf == NULL) return;
		buf_write_page(buf, page);
	}
#else
	lseek(td.tables[table_id].fd, PAGENUM_TO_FILEOFF(page->pagenum), SEEK_SET);
	write(td.tables[table_id].fd, page, PAGE_SIZE);
#endif
}

