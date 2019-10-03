#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <inttypes.h>
#include "table.h"
#include "bpt_internal.h"
#include "api.h"
#include "file.h"

// MAIN
int main( int argc, char ** argv ) {
	int buf_num;
	int64_t input_key;
    int64_t input_values[SIZE_VALUE / sizeof(int64_t)] = { 0,};
	char instruction;
	char table_name[FILENAME_MAX_LENGTH + 1] = { 0,};
	int table_id;
	char read_query[FILENAME_MAX_LENGTH + 1] = { 0,};
	const char* query = read_query;
	int num_columns;
	Table* table;

	if(argc != 2) {
		fprintf(stderr, 
				"Wrong execution of DB\n"
				"Execute DB correctly like\n"
				"./database [num_buf_blocks]\n");
		return FAIL;
	}

//  license_notice();
//	usage_1();  
//	usage_2();

	init_db(atoi(argv[1]));

	printf("> ");
	while (scanf("%c", &instruction) != EOF) {
		switch (instruction) {
		case 'o':	// open table
			scanf("%s %d", table_name, &num_columns);
			open_table(table_name, num_columns);
			break;
		case 'c':	// close table
			scanf("%s", table_name);
			table_id = find_table_id(table_name);
			if(table_id != FAIL)
				close_table(table_id);
			break;
		case 'i':
			scanf("%s %ld", table_name, &input_key);
			table_id = find_table_id(table_name);
			for(int i = 0; i < td.tables[table_id].header->num_columns - 1 ; i++) {
				scanf("%ld", &input_values[i]);
			}
			if(table_id != FAIL) {
				insert(table_id, input_key, input_values);
			//	print_tree(table_id);
			}
			memset(input_values, 0, SIZE_VALUE);
			break;
        case 'd':
			scanf("%s %ld", table_name, &input_key);
			table_id = find_table_id(table_name);
			if(table_id != FAIL) {
				erase(table_id, input_key);
			//	print_tree(table_id);
			}
			break;
		case 'f':
		case 'p':
			scanf("%s %ld", table_name, &input_key);
			table_id = find_table_id(table_name);
			if(table_id != FAIL)
				find_and_print(table_id, input_key);
			break;
		case 'j':
			scanf("%s", read_query);
			printf("%ld\n",join(query));
			memset(read_query, 0, FILENAME_MAX_LENGTH + 1);
			break;
		case 'q':
			while (getchar() != (int)'\n');
			goto exit;
		case 't':
			scanf("%s", table_name);
			table_id = find_table_id(table_name);
			if(table_id != FAIL)
				print_tree(table_id);
			break;
		case 'a':
			scanf("%s", table_name);
			table_id = find_table_id(table_name);
			if(table_id != FAIL)
				analysis(table_id);
			break;
        default:
			usage_2();
			break;
		}
		memset(table_name, 0, FILENAME_MAX_LENGTH + 1);
		while (getchar() != (int)'\n');
		printf("> ");
	}
	printf("\n");

exit:
    shutdown_db();
	return EXIT_SUCCESS;
}
