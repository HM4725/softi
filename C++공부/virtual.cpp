#include<iostream>

using namespace std;

class Base{
public:
	virtual void show(){
		cout<<"Base class\n";
		
	}
	int x;
};

class Derived : public Base{
public:
	void show(){
		cout<<"Derived class\n";
	}
	int y;
};

int main(){
	Base* b;
	Base bb;
	Derived d;

	b=&d;	//upcasting x :pointer, originally possible
	bb=d;	//upcasting o :instance

	b->show();	//output: Derived class

	bb.show();	//output: Base class

	bb.x=3;
//	bb.y=4;		: 'class Base' has no member named 'y';

	b->x=3;
//	b->y=4;		: 'class Base' has no member named 'y';
				// first look at the pointer.
				// then look at the instance.
}

/*
	if virtual keyword on Base, output: Derived class
	else, output: Base class

	virtual: look at Derived class
		use when there are same function in both Base and
		Derived Class.
*/
