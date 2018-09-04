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
	int degree;
	int *array=new int[_number+1];
	/* 소수 선별 */
	for(unsigned int i=2;i<=_number;i++)
		array[i]=i;
	for(unsigned int i=2;i<=_number;i++){
		if(array[i]==0)
			continue;
		for(unsigned int j=2*i;j<=_number;j+=i)
			array[j]=0;
	}

	/* 소인수 분해 */
	for(unsigned int i=2;i<=_number;i++){
		if(array[i]!=0){
			degree=0;
			while(1){
				if(_number%array[i]==0){
					_number/=array[i];
					degree++;	
				}
				else break;
			}
			if(degree!=0){
				factorization<<array[i]<<"^"<<degree;
			}
			if(degree!=0&&_number!=1)
				factorization<<" x ";
		}		
	}	
	delete [] array;

	return factorization.str(); 
}
