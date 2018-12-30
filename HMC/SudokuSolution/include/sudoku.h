#ifndef __SUDOKU_H__
#define __SUDOKU_H__

//#include "heap.h"

#define TRUE 1
#define FALSE 0
#define SOLVE 0
#define CANNOTSOLVE -1

#define ROUNDDOWN(x) (x / 3 * 3)

#define BIT_MASK 1

typedef struct Box Box;
typedef struct Snapshot Snapshot;
typedef struct Heap Heap;

struct Box {
	int m, n;
	int number;
	int row;
	int column;
	int block;
	int ncandi;
	// idx is used for heap
	int idx;
};

struct Snapshot {
	int memo_row[9];
	int memo_column[9];
	int memo_block[3][3];
	Box boxes[9][9];
	Heap* heap;
};

/* API */
int sdk_run(int (*game)[9]);

#endif /* SUDOKU_H */
