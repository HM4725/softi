#include<iostream>

using namespace std;

void func(int a=10, int b=20 ){	//default parameter
	cout<<"First parameter : "<<a;
	cout<<" Second parameter : "<<b<<endl;
}	/* Polymorphism */

int main(void){
//	func();			// 10,20
	func(3);		// 3,20
	func(100,200);	// 100,200
	return 0;
}
