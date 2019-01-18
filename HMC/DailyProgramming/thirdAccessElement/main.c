#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main() {
	char cmd[300];
	list_node_t* tmp;

while(1) {
//	scanf("%[^\n]s", cmd); TODO: why error?
	scanf(" %[^\n]s", cmd);
	switch(cmd[0]) {
		case 'i':
			list_insert((unsigned)atoi(cmd+2));
			break;
		case 'a':
			tmp = list_access(atoi(cmd+2));
			break;
		case 's':
			list_print_third_element();
			break;
		case 'p':
			list_print();
			break;
		case 'q':
			goto exit;
		default:
			puts("type correctly!");
			break;
	}
	memset(cmd, 0, 300);
}
exit:

	return 0;
}
