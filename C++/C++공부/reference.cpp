#include<iostream>
#include<stdio.h>


int main(){
	int nData(10);
	std::cout<<nData<<std::endl;
	// Reference is a kind of NickName.
	int &rData=nData;

	rData=7;
	std::cout<<"nData(10)-->&rData=nData-->rData=7"<<std::endl;
	std::cout<<"nData:" << nData <<std::endl;
	std::cout<<"&nData:" << &nData <<std::endl;
	std::cout<<"&rData:" << &rData <<std::endl;

	// WHY?? 

	int nNewData(20);
	
	int* pnData= &nData;
	std::cout<<"pnData=&nData, *pnData=5"<<std::endl;
	*pnData=5;	//nData=5;
	std::cout<<"nData:" << nData <<std::endl;
	std::cout<<"nNewData:" << nNewData <<std::endl;
	std::cout<<"*pnData:" << *pnData <<std::endl;
	
	pnData=&nNewData;
	std::cout<<"pnData=&nData, *pnData=";
	std::cin>>*pnData;	//std::cin>>nNewData;
	std::cout<<"nData:" << nData <<std::endl;
	std::cout<<"nNewData:" << nNewData <<std::endl;
	std::cout<<"*pnData:" << *pnData <<std::endl;

	std::cout<<">>>rData:"<<rData<<std::endl;
//	printf("rData:%p",rData);
	std::cout<<">>>&nData:"<<&nData<<std::endl;
	//  --> Question

	return 0;
}

/*
Why do we use Reference?
	Because of the problem of Pointer.
	Pointer is a variable.
	Pointer can change.
	Pointer can point another variable.

But Reference points just one variable.

Reference =~ const Pointer   but different type.

<WIKIPEDIA>
In the C++ programming language, a reference is a simple reference datatype that is less powerful but safer than the pointer type inherited from C. The name C++ reference may cause confusion, as in computer science a reference is a general concept datatype, with pointers and C++ references being specific reference datatype implementations. The definition of a reference in C++ is such that it does not need to exist. It can be implemented as a new name for an existing object (similar to rename keyword in Ada).
*/
