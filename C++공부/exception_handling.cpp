#include<iostream>

using namespace std;

void func(int a, int b){
	if(b<=0) throw a;
	double dpg=a/static_cast<double>(b);
	cout<<a<<" donuts.\n"
		<<b<<" glasses of milk.\n"
		<<"You have "<<dpg
		<<" donuts for each glass of milk.\n";
}
///////////////////////////////////////////////
template<class T>
void tempfunc(T& temp){
	if(temp<=0) throw temp;
	cout<<"Template:"<<temp<<endl;
}
////////////////////////////////////////////////
void function1(){
	throw 3;
}
void function2(){
	throw 2.2;
}
void function3(){
	throw 'a';
}
void function4(){
	char input;
	cout<<"int(i) or double(d) or char(c) :"<<endl;
	cin>>input;
	if(input='i')	function1();
	else if(input='d')	function2();
	else if(input='c')	function3();
	else {
		cout<<"error!\n";
		throw -1;
	}
}

//////////////////////////////////////////////////
int main(){
	int donuts;
	int milk;

	cout<<"Enter number of donuts:";
	cin>>donuts;
	cout<<"Enter number of glasses of milk:";
	cin>>milk;
	try{
		func(donuts,milk);
	}
	catch(int exception){
		cout<<exception<<" donuts, and No milk!\n"
			<<"Go buy some milk.\n";
	}	//try하고 throw되면 catch를 실행 

/////////////////////////////////////////////////////////

	try{	//위에 catch가 실행되도 계속 코드 진행
		double dpg=donuts/static_cast<double>(milk);
		tempfunc(dpg);	//double exception!
		//tempfunc(milk);	//int exception!
	}
	catch(int exception){
		cout<<"int exception!\n";
	}
	catch(double exception){
		cout<<"double exception!\n";
	}
//////////////////////////////////////////////////////////
	try{
		function4();
	}
	catch(int e){
		if(exception==-1){
			cout<<"error!"<<endl;
			return -1;
		}
		cout<<"int exception!"<<endl;
	}
	catch(double e){
		cout<<"double exception!"<<endl;
	}
	catch(char e){
		cout<<"char exception!"<<endl;
	}
	return 0;
}
