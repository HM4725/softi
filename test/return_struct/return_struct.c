#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int a;
	int b;
	char c;
}Point;

Point func();

void main(){
	Point temp;
	temp.a=0; temp.b=0; temp.c=0;
	printf("temp=%p\n",&temp);
	puts("temp=func();");
	temp=func();
	printf("temp=%p\n",&temp);
	printf("temp.a=%d,temp.b=%d,temp.c=%d\n",temp.a,temp.b,temp.c);
}

Point func(){
	puts("start of func()");
	Point temp;
	temp.a=1; temp.b=1; temp.c=1;
	printf("func():temp=%p\n",&temp);
	puts("end of func()");
	
	return temp;
}
