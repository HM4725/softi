#include<stdio.h>

int main(){
	int* p1;
	const int* p2;
	const int** pp2;
	const int n=13;

//	p1=p2;
	/* 5번 줄의 const는 p2가 가리키는 int변수의 값을 상수화한다.
	   만약 p1=p2가 가능하다면, p1을 통해 p2가 가리키는 변수의 값을 바꿀 수 있기 때문에
	   nonconst pointer = address of const pointer 연산은 불가능하다.
	*/
	p2=p1;
//	pp2=&p1;
	/* 6번 줄의 const는 pp2가 가리키고 가리키는 int변수의 값을 상수화한다.
	   만약 pp2=&p1이 가능하다면, p1을 통해 p1가 가리키는 int변수의 값을 바꿀 수 있기 때문에
	   const double pointer = address of nonconst pointer 연산은 불가능하다.
	*/
	*pp2=&n;
	*p1=10;

	return 0;
}
