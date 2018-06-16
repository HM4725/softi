#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<assert.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	if (argc !=2){
		fprintf(stderr, "usage: cpu <string>\n");
		exit(1);
	}
	char *str=argv[1];
	int count=0;

	while(count++<5){
		printf("%s\n",str);
		usleep(500000);
	}
	return 0;
}	
