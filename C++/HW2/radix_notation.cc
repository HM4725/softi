#include<stdio.h>
#include<iostream>
#include<string>

using namespace std;

string RadixNotation(unsigned int , unsigned int );

int main(int argc, char **argv){
	if(argc <2) return -1;
	unsigned int radix;
	sscanf(argv[1],"%u",&radix);
	if(radix<2||radix>36) return -1;
	for(int i=2;i<argc;++i){
		unsigned int number;
		sscanf(argv[i],"%u",&number);
		cout<<RadixNotation(number,radix)<<endl;
	}
	return 0;
}

string RadixNotation(unsigned int number, unsigned int radix){
	unsigned int remainder,m,n;
	string change1;
	string change2;
	char hold;

	for(m=0;number!=0;m++){	
		remainder=number%radix;
		number/=radix;
		if(remainder<10){
			hold=(char)remainder+48; //0~9(char)
			change1+=hold;
		}
		else{
			hold=(char)remainder+87; //a~z(char)
			change1+=hold;
		}
	}
	for(n=0;n<m;n++){
		change2+=change1[m-n-1];
	}
	return change2;
}
