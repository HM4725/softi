#ifndef __TABLE_H__
#define __TABLE_H__

#include "buffer.h"

#define DISUSED 0
#define NOTOPEN -1

#define TABLE_MAX_ID			10
#define FILENAME_MAX_LENGTH		256

typedef struct _Table {
	// file descriptor
	int fd;
	HeaderPage* header;
	char* name;
	// Used for buffer search
	Buf** hash_table;
	pagenum_t hash_size;
	// TODO: Used for join
	uint64_t num_records;
} Table;

typedef struct _TableDirectory {
	// tables[0]: disused
	Table tables[TABLE_MAX_ID + 1];
	int num_open_tables;
	int capacity;
} TableDirectory;

/* GLOBAL */
extern TableDirectory td;

#endif /* TABLE_H */
