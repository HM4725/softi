#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define INT_MAX 2147483647

int Zero();
bool IsZero(int);
bool Equal(int,int);
int Successor(int);
int Add(int,int);
int Subtract(int,int);

int main(int argc, char** args){
	int x=atoi(args[1]);
	int y=atoi(args[2]);

	printf("Is %d zero? %s\n",x,IsZero(x) ? "True":"False");
	printf("Is %d zero? %s\n",y,IsZero(y) ? "True":"False");
	printf("Does %d equal %d? %s\n",x,y,Equal(x,y)?"True":"False");
	printf("%d's next number is %d\n",x,Successor(x));
	printf("%d's next number is %d\n",y,Successor(y));
	printf("%d + %d = %d\n",x,y, Add(x,y));
	printf("%d - %d = %d\n",x,y,Subtract(x,y));

	return 0;
}

int Zero(){ return 0; }
bool IsZero(int _x){ return _x==Zero(); }
bool Equal(int _x, int _y){ return _x==_y; }
int Successor(int _x){ 
	long int num=_x;
	return num+1<INT_MAX ? num+1: num;
}
int Add(int _x, int _y){
	long int num1=_x;
	long int num2=_y;
	return num1+num2<INT_MAX ? num1+num2 :INT_MAX; 
	/* num1<0, num2<0 , num1+num2<-INT_MAX ?? */
}
int Subtract(int _x, int _y){
	long int num1=_x;
	long int num2=_y;
	return num1>num2 ? num1-num2 : 0; 
}
