#include<iostream>
using std::cout;
using std::cin;
using std::endl;

class Parent{
	public:
		Parent() { cout<<" Parent "; }
		virtual ~Parent() { cout<<" ~Parent "; }
};

class Child : public Parent {
	public:
		Child() { cout<<" Child "; }
		~Child() { cout<<" ~Child "; }
};

class Test : public Child {
	public:
		Test() { cout<<" Test "; }
		~Test() { cout<<" ~Test "; }
};

int main() {
	{
		cout << "<Child child>"<<endl;
		Child child;	// Parent Child
		cout<< endl;
	}	// ~Child ~Parent
	cout<<endl;
	{
		cout << "<Test test>"<<endl;
		Test test;	// Parent Child Test
		cout<<endl;
	}	// ~Test ~Child ~Parent
	cout<<endl;
	{
		cout << "<Parent* pt=new Test>"<<endl;
		Parent* pt=new Test;
		cout<<endl;
		delete pt;	
		/*delete 미사용시 아무것도 호출되지 않음.
		  delete 사용시 ~Parent만 호출됨
		  ~Parent()에 virtual키워드를 써주면 모든 소멸자가 호출됨 */
	}
	cout<<endl;
	return 0;
}
