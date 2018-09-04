#include<iostream>
using namespace std;

inline int add(int a,int b);
int add(int a,int b){
	return a+b;
}

int add_stack(int a,int b){
	return a+b;
}

inline void swap(int a, int b);
void swap(int a, int b){
	int hold=a;
	a=b;
	b=hold;
}

void swap_stack(int a, int b){
	int hold=a;
	a=b;
	b=hold;
}


int main(){
	int c=add(5,3);
	int d=add_stack(5,3);

	cout<<c<<","<<d<<endl;

	int a=0;
	int b=7;

	cout<<a<<","<<b<<endl;
	swap_stack(a,b);
	cout<<a<<","<<b<<endl;
	swap(a,b);
	cout<<a<<","<<b<<endl;


	return 0;
}
