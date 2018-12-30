#ifndef __HEAP_H__
#define __HEAP_H__

#include "sudoku.h"

typedef struct Heap Heap;
typedef struct Box Box;

struct Heap {
	Box** boxes;
	int size;
	int capacity;
};

Heap* heap_create(int capacity);
void heap_build(Heap* heap);
Heap* heap_copy(Heap* heap, Box (*boxes)[9]);
void heap_input(Heap* heap, Box* box);
void heap_update(Heap* heap, Box* box);
void heap_heapify(Heap* heap, int pos);
Box* heap_delete_min(Heap* heap);
void heap_destroy(Heap* heap);

#endif /* HEAP_H */
