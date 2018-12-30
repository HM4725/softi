#include <stdio.h>
#include "sudoku.h"

int main(int argc, char* argv[]) {
	FILE* ifp = NULL;
	FILE* ofp = NULL;
	int game[9][9] = { 0,};
	int num;
	int m=0;
	int n=0;

	if(argc < 2) return -1;

	ifp = fopen(argv[1], "r");
	while(fscanf(ifp, "%d", &num) != EOF) {
		game[m][n] = num;
		if(++n >= 9) {
			m++;
			n = 0;
		}
	}

	if(sdk_run(game) == CANNOTSOLVE)
		return -1;
	
	ofp = fopen("result", "w");
	for(m = 0; m < 9; m++) {
		for(n = 0; n < 9; n++) {
			fprintf(ofp,"%d ", game[m][n]);
		}
		fprintf(ofp,"\n");
	}

	return 0;
}
