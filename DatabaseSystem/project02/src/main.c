#include "bpt.h"

// MAIN

int main( int argc, char ** argv ) {

    char * input_file;
	char buf[120];
    FILE * fp;
    node * root;
    int input, range2;
    char instruction;

    root = NULL;

    if (argc > 1) {
		input_file = argv[1];
		open_db(input_file);
    } else {
		fprintf(stderr,"no!\n");
		exit(EXIT_FAILURE);
	}

    printf("> ");
    while (scanf("%c", &instruction) != EOF) {
        switch (instruction) {
        case 'd':
            scanf("%d", &input);
            delete(input);
            break;
        case 'i':
            scanf("%d", &input);
			memset(buf,0,120);
			scanf("%s", buf);
            insert(input, buf);
            break;
		case 'f':
			scanf("%d", &input);
			printf("record: < %d, %s >\n", input, find(input));
			break;
		case 'q':
			goto exit;
        default:
			fprintf(stderr, "default\n");
            break;
        }
        while (getchar() != (int)'\n');
        printf("> ");
    }
exit:
    printf("\n");

    return EXIT_SUCCESS;
}
