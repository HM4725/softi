#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<wait.h>

int main(){
	
	printf("Start of the program\n");

	int pid = fork();
	int status; 

	if(pid>0) {
		printf("parent: child=%d\n",pid);
		pid=wait(&status);
		printf("child %d is done\n", pid);
	} else if(pid==0){
		printf("child: exiting\n");
		exit(0);
	} else {
		printf("fork error\n");
	}

	printf("End of the program\n");

	return 0;
}
