#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "table.h"
#include "buffer.h"
#include "panic.h"

Buf* buf_search(int table_id, pagenum_t key) {
	Buf** tmp;
	Table* table = &td.tables[table_id];

	if(key >= table->hash_size) {
		// rehashing
		table->hash_size *= 2;
		tmp = (Buf**)malloc(sizeof(Buf*) * table->hash_size);
		if(tmp == NULL) {
			PANIC("failed to alloc a new buf hash table");
		}
		memset(tmp, 0, table->hash_size);
		for(int i = 0; i < table->hash_size/2 ; i++) {
			tmp[i] = table->hash_table[i];
		}
		free(table->hash_table);
		table->hash_table = tmp;
	}

	return table->hash_table[key];
}

void hash_insert(int table_id, pagenum_t key, Buf* val) {
	Table* table = &td.tables[table_id];
	table->hash_table[key] = val;
}

void hash_delete(int table_id, pagenum_t key) {
	Table* table = &td.tables[table_id];
	table->hash_table[key] = NULL;
}

void buf_make_free() {
	Buf* free = NULL;
	free = (Buf*)malloc(sizeof(Buf));
	if(free == NULL) {
		PANIC("Failed to make a free buffer block");
	}
	// free buffer block doesn`t use prev field
	memset(free, 0, sizeof(Buf));
	free->next = bufmgr.free_buf;
	bufmgr.free_buf = free;
}

Buf* buf_get_free() {
	Buf* free;
	free = bufmgr.free_buf;
	if(free != NULL) {
		bufmgr.free_buf = free->next;
	}
	return free;
}

int buf_release(Buf* buf) {

	if(buf->is_pinned > 0) {
		return FAIL;
	}

	Buf* prev;
	Buf* next;

	buf->is_pinned++;
	buf_sync_file(buf);

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

	hash_delete(buf->table_id, buf->pagenum);
	memset(buf, 0, sizeof(Buf));
	buf->next = bufmgr.free_buf;
	bufmgr.free_buf = buf;

	return SUCCESS;
}

Buf* buf_find_lru() {
	Buf* buf = bufmgr.first_buf->prev;
	while(buf->is_pinned) {
		buf = buf->prev;
	}
	buf->is_pinned++;

	return buf;
}

void buf_overwrite(Buf* buf, int table_id, pagenum_t pagenum) {
	
	Table* table = &td.tables[table_id];

	buf_sync_file(buf);
	hash_delete(table_id, buf->pagenum);
	lseek(table->fd, PAGENUM_TO_FILEOFF(pagenum), SEEK_SET);
	read(table->fd, buf, PAGE_SIZE);
	buf->table_id = table_id;
	buf->pagenum = pagenum;
	buf->is_dirty = 0;
	hash_insert(table_id, pagenum, buf);
}

Buf* buf_alloc(int table_id, pagenum_t pagenum) {

	Table* table = NULL;
	Buf* buf = buf_get_free();
	// buf_alloc is only used when there is a free buffer block.
	// TODO: thread? lock?
	assert(buf != NULL);

	table = &td.tables[table_id];

	lseek(table->fd, PAGENUM_TO_FILEOFF(pagenum), SEEK_SET);
	read(table->fd, buf, PAGE_SIZE);
	buf->table_id = table_id;
	buf->pagenum = pagenum;
	buf->is_dirty = 0;
	buf->is_pinned = 1;
	buf->prev = NULL;
	buf->next = NULL;

	if(bufmgr.first_buf == NULL){
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
	hash_insert(table_id, pagenum, buf);

	return buf;
}

void buf_sync_file(Buf* buf) {

	int tid;
	Table* table;

	if(buf->is_dirty) {

		buf->is_pinned++;

		tid = buf->table_id;
		table = &td.tables[tid];

 		lseek(table->fd, PAGENUM_TO_FILEOFF(buf->pagenum), SEEK_SET);
		write(table->fd, buf, PAGE_SIZE);

		buf->is_pinned--;
	}
}

void buf_move_to_first(Buf* buf) {

	Buf* prev;
	Buf* next;

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

}

void buf_read_page(Buf* buf, Page* page) {
	assert(buf != NULL && page != NULL);

	Buf* prev;
	Buf* next;

	memcpy(page, buf, PAGE_SIZE);
	page->pagenum = buf->pagenum;

	if(buf != bufmgr.first_buf) {
		buf_move_to_first(buf);
	}
}

void buf_write_page(Buf* buf, const Page* page) {
	assert(buf != NULL && page != NULL);

	Buf* prev;
	Buf* next;

	memcpy(buf, page, PAGE_SIZE);
	buf->is_dirty++;

	if(buf != bufmgr.first_buf) {
		buf_move_to_first(buf);
	}
}
