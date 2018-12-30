#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "swap.h"

Heap* heap_create(int capacity) {
	Heap* heap;

	heap = (Heap*)malloc(sizeof(Heap));
	heap->boxes = (Box**)malloc(sizeof(Box*) * (capacity + 1));
	memset(heap->boxes, 0, sizeof(Box*) * (capacity + 1));
	heap->size = 0;
	heap->capacity = capacity;

	return heap;
}

void heap_build(Heap* heap) {
	int i;

	for(i = heap->size / 2; i != 0; i--)
		heap_heapify(heap, i);
}

Heap* heap_copy(Heap* heap, Box (*boxes)[9]) {
	Heap* new_heap;
	int i;
	int m, n;

	new_heap = (Heap*)malloc(sizeof(Heap));
	new_heap->size = heap->size;
	new_heap->capacity = heap->capacity;
	new_heap->boxes = (Box**)malloc(sizeof(Box*) * new_heap->capacity);
	
	for(i = 1; i <= new_heap->size; i++) {
		m = heap->boxes[i]->m;
		n = heap->boxes[i]->n;
		new_heap->boxes[i] = &boxes[m][n];
		new_heap->boxes[i]->idx = i;
	}

	return new_heap;
}

void heap_input(Heap* heap, Box* box) {

	heap->boxes[++heap->size] = box;
	box->idx = heap->size;
}

void heap_update(Heap* heap, Box* box) {
	int i = box->idx;

	while(i != 1 && heap->boxes[i]->ncandi < heap->boxes[i/2]->ncandi) {
		SWAP(heap->boxes[i], heap->boxes[i/2]);
		i /= 2;
	}
}

void heap_heapify(Heap* heap, int pos) {
	int i, child;

	for(i = pos; i * 2 <= heap->size; i = child) {
		child = i * 2;
		if(child != heap->size
				&& heap->boxes[child]->ncandi
				> heap->boxes[child + 1]->ncandi) child++;
		if(heap->boxes[i]->ncandi > heap->boxes[child]->ncandi)
			SWAP(heap->boxes[i], heap->boxes[child]);
		else break;
	}
}

Box* heap_delete_min(Heap* heap) {
	Box* min = heap->boxes[1];
	Box* last = heap->boxes[heap->size--];

	heap->boxes[1] = last;
	heap->boxes[1]->idx = 1;
	heap_heapify(heap, 1);

	return min;
}

void heap_destroy(Heap* heap) {

	free(heap->boxes);
	free(heap);
}
