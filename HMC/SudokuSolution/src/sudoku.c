#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sudoku.h"
#include "heap.h"

int (*org)[9] = NULL;
Snapshot* cur_ss = NULL;
int is_first = TRUE;

static
void sdk_init(int (*game)[9]) {

	org = game;
	cur_ss = (Snapshot*)malloc(sizeof(Snapshot));
	memset(cur_ss, 0, sizeof(Snapshot));
	cur_ss->heap = heap_create(81);
}

static
int sdk_set_row(Snapshot* ss, int i, int j) {
	int n;
	int row = 0;
	int num;
	int mask;

	if(ss->memo_row[i] != 0)
		return ss->memo_row[i];

	for(n = 0; n < 9; n++) {
		num = is_first ? org[i][n] : ss->boxes[i][n].number;
		if(num != 0) {
			mask = 1 << (num - 1);
			row |= mask;
		}
	}
	ss->memo_row[i] = row;

	return row;
}

static
int sdk_set_column(Snapshot* ss, int i, int j) {
	int m;
	int column = 0;
	int num;
	int mask;

	if(ss->memo_column[j] != 0)
		return ss->memo_column[j];

	for(m = 0; m < 9; m++) {
		num = is_first ? org[m][j] : ss->boxes[m][j].number;
		if(num != 0) {
			mask = 1 << (num - 1);
			column |= mask;
		}
	}
	ss->memo_column[j] = column;

	return column;
}

static
int sdk_set_block(Snapshot* ss, int i, int j) {
	int m, n;
	int block = 0;
	int num;
	int mask;

	i = ROUNDDOWN(i);
	j = ROUNDDOWN(j);

	if(ss->memo_block[i/3][j/3] != 0)
		return ss->memo_block[i/3][j/3];

	for(m = i; m < i + 3; m++) {
		for(n = j; n < j + 3; n++) {
			num = is_first ? org[m][n] : ss->boxes[m][n].number;
			if(num != 0) {
				mask = 1 << (num - 1);
				block |= mask;
			}
		}
	}
	ss->memo_block[i/3][j/3] = block;

	return block;
}

static
int sdk_calculate_candidates(Snapshot* ss, int i, int j) {
	Box* pb = &(ss->boxes[i][j]);
	int candidates;
	int k;
	int ncandi = 0;
	int mask = 1;

	candidates = pb->row | pb->column | pb->block;
	candidates = ~candidates;

	for(k = 0; k < 9; k++) {
		if((candidates & mask) != 0) {
			ncandi++;
		}
		mask <<= 1;
	}
	return ncandi;
}

static
void sdk_set_boxes() {
	int i, j;
	Box* box;

	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			box = &(cur_ss->boxes[i][j]);
			box->m = i;
			box->n = j;
			box->number = org[i][j];
			if(org[i][j] == 0) {
				box->row = sdk_set_row(cur_ss, i, j);
				box->column = sdk_set_column(cur_ss, i, j);
				box->block = sdk_set_block(cur_ss, i, j);
				box->ncandi = sdk_calculate_candidates(cur_ss, i, j);
				heap_input(cur_ss->heap, box);
			}
		}
	}

	heap_build(cur_ss->heap);
	is_first = FALSE;
}

static
Snapshot* sdk_take_snapshot(Snapshot* ss) {
	Snapshot* new_ss = NULL;

	new_ss = (Snapshot*)malloc(sizeof(Snapshot));
	memcpy(new_ss, ss, sizeof(Snapshot));
	new_ss->heap = heap_copy(ss->heap, new_ss->boxes);

	return new_ss;
}

static
void sdk_erase_snapshot(Snapshot* ss) {

	heap_destroy(ss->heap);
	free(ss);
}

static
void sdk_update_box(Snapshot* ss, Box* box, int num) {
	int m, n;
	int i, j;
	int l, k;
	Box* member;

	m = box->m;
	n = box->n;
	box->number = num;
	box->ncandi = 0;
	ss->memo_row[m] = 0;
	ss->memo_column[n] = 0;
	i = ROUNDDOWN(m);
	j = ROUNDDOWN(n);
	ss->memo_block[i/3][j/3] = 0;

	for(k = 0; k < 9; k++) {
		member = &ss->boxes[m][k];
		if(member->number == 0) {
			member->row = sdk_set_row(ss, m, k);
			member->ncandi = sdk_calculate_candidates(ss, m, k);
			heap_update(ss->heap, member);
		}
	}

	for(l = 0; l < 9; l++) {
		member = &ss->boxes[l][n];
		if(member->number == 0) {
			member->column = sdk_set_column(ss, l, n);
			member->ncandi = sdk_calculate_candidates(ss, l, n);
			heap_update(ss->heap, member);
		}
	}

	for(l = i; l < i + 3; l++) {
		for(k = j; k < j + 3; k++) {
			member = &ss->boxes[l][k];
			if(member->number == 0) {
				member->block = sdk_set_block(ss, l, k);
				if(l != m && k != n) {
					member->ncandi = sdk_calculate_candidates(ss, l, k);
					heap_update(ss->heap, member);
				}
			}
		}
	}
}

static
int sdk_solve_game(Snapshot* ss) {
	Snapshot* new_ss;
	Box* box;
	Box* new_box;
	int candis;
	int ncandi;
	int candi;
	int mask;
	int i, j;

	while(ss->heap->size > 0) {
		box = heap_delete_min(ss->heap);
		candis = ~(box->row | box->column | box->block);
		ncandi = box->ncandi;
		candi = 1;
		mask = 1;
		if(ncandi == 1) {
			while((candis & mask) == 0) {
				candi++;
				mask <<= 1;
			}
			sdk_update_box(ss, box, candi);
		} else if(ncandi > 1) {
			for(i = 0; i < ncandi; i++) {
				new_ss = sdk_take_snapshot(ss);
				while((candis & mask) == 0) {
					candi++;
					mask <<= 1;
				}
				new_box = &new_ss->boxes[box->m][box->n];
				sdk_update_box(new_ss, new_box, candi);
				if(sdk_solve_game(new_ss) == SOLVE) {
					sdk_erase_snapshot(new_ss);
					return SOLVE;
				} else {
					sdk_erase_snapshot(new_ss);
					candi++;
					mask <<= 1;
				}
			}
			return CANNOTSOLVE;
		} else {
			return CANNOTSOLVE;
		}
	}

	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			if(org[i][j] == 0)
				org[i][j] = ss->boxes[i][j].number;
		}
	}

	return SOLVE;
}

static
int sdk_solve() {
	int result;

	result = sdk_solve_game(cur_ss);
	sdk_erase_snapshot(cur_ss);

	return result;
}

int sdk_run(int (*game)[9]) {

	sdk_init(game);
	sdk_set_boxes();
	return sdk_solve();
}

