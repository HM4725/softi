#include <stdio.h>

int main() {

	static char arr[2][10] = {
		"0123456789",
		"0123456789"
	};
	int i, j;
	
	printf("%s\n",
			"static char arr[2][10] = {\n"
			"\t\t\"0123456789\",\n"
			"\t\t\"0123456789\"\n"
			"};");

	puts("first");
	for(i = 0; i < 2; i++) {
		for(j = 0; j < 10; j++) {
			printf("&arr[%d][%d]: %p, arr[%d][%d]: \'%c\'\n", i, j, &arr[i][j], i, j, arr[i][j]);
		}
	}
	puts("second");
	for(i = 0; i < 2; i++) {
		printf("&arr[%d]: %p\n", i, &arr[i]);
	}

	return 0;
}
