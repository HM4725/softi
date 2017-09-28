#include<iostream>
#include<stdio.h>
#include<sstream>
using namespace std;

string primeFactorization(unsigned int);

int main(int argc, char** argv){
	if(argc<1)
		return -1;
	unsigned int number;
	sscanf(argv[1],"%u",&number);
	
	cout<<primeFactorization(number)<<endl;

	return 0;
}

string primeFactorization(unsigned int _number){
	stringstream factorization;
	int i,division=2;

	while(true){
		if(_number%division==0){
			for(i=0;_number%division==0;i++)
				_number/=division;
				factorization<<division<<"^"<<i;
			if(_number!=1)
				factorization<<" x ";
		}
		if(_number==1)
			break;
		division++;
	}
	return factorization.str();
}
