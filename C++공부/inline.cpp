#include<iostream>
using namespace std;

inline int add(int a,int b);
int add(int a,int b){
	return a+b;
}

int add_stack(int a,int b){
	return a+b;
}

int main(){
	int c=add(5,3);
	int d=add_stack(5,3);

	cout<<c<<","<<d<<endl;

	return 0;
}
