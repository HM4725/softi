#include <stdio.h>

int main() {
	char* arr = "hello wolrd\n";

	for(int i = 0; i[arr] != 0; i++) {
		printf("%c", i[arr]);
	}

	return 0;
}

/*
 *	BYTE [arr+i] 표현
 *		1. *(arr+i)
 *		2. *(i+arr)
 *		3. arr[i]
 *		4. i[arr]
 */
