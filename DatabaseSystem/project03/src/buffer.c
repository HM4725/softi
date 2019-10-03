#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "buffer.h"
#include "panic.h"

// TODO: speed up (algorithm)
Buf* find_buf(int table_id, pagenum_t pagenum) {
	Buf* buf;
	for(buf = bufmgr.first_buf; buf!= NULL; buf = buf->next) {
		if(buf->table_id == table_id && buf->pagenum == pagenum) {
			break;
		}
	}
	return buf;
}

Buf* insert_buf(int table_id, pagenum_t pagenum) {
	if(bufmgr.num_pages >= bufmgr.capacity) {
		fprintf(stderr, "The buffer is full.\n");
		return NULL;
	}
	
	Table* table = NULL;
	Buf* buf = NULL;

	table = &td.tables[table_id];
	buf = (Buf*)malloc(sizeof(Buf));
	if(buf == NULL) {
		PANIC("failed to allocate a buffer block");
	}

	lseek(table->fd, PAGENUM_TO_FILEOFF(pagenum), SEEK_SET);
	read(table->fd, buf, PAGE_SIZE);
	buf->table_id = table_id;
	buf->pagenum = pagenum;
	buf->is_dirty = 0;
	buf->is_pinned = 1;
	buf->prev = NULL;
	buf->next = NULL;

	if(bufmgr.num_pages == 0){
		bufmgr.first_buf = buf;
		buf->prev = buf;
	} else {
		bufmgr.first_buf->is_pinned++;
		bufmgr.first_buf->prev->is_pinned++;

		buf->next = bufmgr.first_buf;
		buf->prev = bufmgr.first_buf->prev;
		bufmgr.first_buf->prev = buf;
		bufmgr.first_buf = buf;

		buf->prev->is_pinned--;
		buf->next->is_pinned--;
	}
	buf->is_pinned--;
	bufmgr.num_pages++;

	return buf;
}

int delete_buf(Buf* buf) {
	assert(buf != NULL && bufmgr.num_pages != 0);

	if(buf->is_pinned > 0) {
		return FAIL;
	}

	Buf* prev;
	Buf* next;

	buf->is_pinned++;
	if(buf->is_dirty){
		update_file(buf);
	}

	buf->prev->is_pinned++;
	if(buf->next == NULL) {
		bufmgr.first_buf->is_pinned++;
	} else {
		buf->next->is_pinned++;
	}
	prev = buf->prev;
	next = buf->next == NULL ? bufmgr.first_buf : buf->next;

	if(bufmgr.first_buf == buf) {
		bufmgr.first_buf = buf->next;
	} else {
		prev->next = buf->next;
	}
	next->prev = prev;
	prev->is_pinned--;
	next->is_pinned--;

	free(buf);
	bufmgr.num_pages--;

	return SUCCESS;
}

void update_file(Buf* buf) {
	assert(buf != NULL && bufmgr.num_pages != 0);

	int tid;
	Table* table;

	tid = buf->table_id;
	table = &td.tables[tid];

	lseek(table->fd, PAGENUM_TO_FILEOFF(buf->pagenum), SEEK_SET);
	write(table->fd, buf, PAGE_SIZE);
}

void buf_read_page(Buf* buf, Page* page) {
	assert(buf != NULL && page != NULL);

	Buf* prev;
	Buf* next;

	// begin & read page
	buf->is_pinned++;
	memcpy(page, buf, PAGE_SIZE);
	page->pagenum = buf->pagenum;

	if(buf == bufmgr.first_buf) {
		// end if first buf
		buf->is_pinned--;
		return;
	}

	// 1. remove buf
	buf->prev->is_pinned++;
	if(buf->next == NULL) {
		bufmgr.first_buf->is_pinned++;
	} else {
		buf->next->is_pinned++;
	}
	prev = buf->prev;
	next = buf->next == NULL ? bufmgr.first_buf : buf->next;

	prev->next = buf->next;
	next->prev = prev;

	prev->is_pinned--;
	next->is_pinned--;

	// 2. move the buf to first_buf
	bufmgr.first_buf->prev->is_pinned++;
	bufmgr.first_buf->is_pinned++;
	prev = bufmgr.first_buf->prev;
	next = bufmgr.first_buf;

	next->prev = buf;
	buf->prev = prev;
	buf->next = next;
	bufmgr.first_buf = buf;

	prev->is_pinned--;
	next->is_pinned--;

	// end
	buf->is_pinned--;
}

void buf_write_page(Buf* buf, Page* page) {
	assert(buf != NULL && page != NULL);

	Buf* prev;
	Buf* next;

	// begin & write page
	buf->is_pinned++;
	memcpy(buf, page, PAGE_SIZE);
	buf->is_dirty++;

	if(buf == bufmgr.first_buf) {
		// end if first buf
		buf->is_pinned--;
		return;
	}

	// 1. remove buf
	buf->prev->is_pinned++;
	if(buf->next == NULL) {
		bufmgr.first_buf->is_pinned++;
	} else {
		buf->next->is_pinned++;
	}
	prev = buf->prev;
	next = (buf->next == NULL ? bufmgr.first_buf : buf->next );

	prev->next = buf->next;
	next->prev = prev;

	prev->is_pinned--;
	next->is_pinned--;

	// 2. move the buf to first_buf
	bufmgr.first_buf->prev->is_pinned++;
	bufmgr.first_buf->is_pinned++;
	prev = bufmgr.first_buf->prev;
	next = bufmgr.first_buf;

	next->prev = buf;
	buf->prev = prev;
	buf->next = next;
	bufmgr.first_buf = buf;

	prev->is_pinned--;
	next->is_pinned--;

	// end
	buf->is_pinned--;
}
