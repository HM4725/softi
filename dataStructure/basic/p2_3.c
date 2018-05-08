#include<stdlib.h>
#include<stdio.h>

void main(int argv, char* argc[]){
	int num=atoi(argc[1]);
	char** names=(char**)malloc(sizeof(char*)*num);
//	num=atoi(argc[1]);: num을 7번째줄 아래서 정해주면 메모리오류남>> 왜?
	for(int i=0;i<num;i++){
		names[i]=(char*)malloc(sizeof(char)*30);
	}
	//char** names=(char**)malloc(sizeof(char[30])*num);은 왜 오류?

	printf("enter %d names:\n",num);

	for(int i=0;i<num; i++){
		scanf("%s",names[i]);
	}

	printf("the names you entered:\n");
	for(int i=0;i<num; i++){
		printf("%s\n",names[i]);
	}


	for(int i=0;i<num;i++){
		free(names[i]);
	}
	free(names);
}
