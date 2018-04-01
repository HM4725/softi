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
	virtual void show(){
		cout<<"Derived class\n";
	}/* 자식클래스에 virtual 쓰는 이유:
		부모와 자식클래스가 서로 상속관계에 있는
		상황을 대비하여 둘다 virtual 써줌(학부난이도x) */
	int y;
};

int main(){
	Base* pb;
	Base b;
	Derived* pd;
	Derived d;

	pb=&d;	//upcasting o :pointer!
	b=d;	//upcasting x :instance 단순 대입!
		/* 컴파일러가 copy constructor, operator=를 자동 작성
		   해준다고 생각
		 	default , move constructor도 자동으로 작성*/

//	pd=pb;	//invalid conversion from 'Base*' to 'Derived*'
//	pd=&b;
	pb=new Base;
	pd=dynamic_cast<Derived*>(pb);	//downcasting
//	d=dynamic_cast<Derived>(b);	//downcasting: pointer or reference!

	pb->show();	//output: Derived class

	b.show();	//output: Base class
	b.x=3;
//	b.y=4;		: 'class Base' has no member named 'y';

	pb->x=3;
//	pb->y=4;		: 'class Base' has no member named 'y';
				// first look at the pointer.	(지정형식) 중요!
				// then look at the instance.	(실형식)
	pd->show();	//output: Derived class
	pd->y=3;
	pd->x=4;
	delete pb;
}

/*
	if virtual keyword on Base, output: Derived class
	else, output: Base class

	virtual: Look at Derived class, This isn`t a real function.
		use when there are same function in both Base and
		Derived Class.
*/
