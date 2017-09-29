#include<iostream>

int Sum(int num1, int num2){
	return num1+num2;
}

int main(){
	int a=3; // C language style , a: name
	int b(10); // C++ style	, b : object, instance
	int c(b);  // clone
//	int (10); // ??!! --> no name instance (declaration? definition?)
	auto d(c);

	std::cout<<"hello world " << c<<" " <<a <<std::endl;
	std::cout<<"size of ("<<d<<") : "<< sizeof(d)<<std::endl;

	int e=Sum(a,b);
	auto f(Sum(b,d));
	std::cout<<"e="<<e<<" ,f="<<f<<std::endl;

	return 0;
}

/* 
1. auto instance can be used in C++11.
2. GCC : C++11 Compile instruction option : -std=c++0x
*/ 
