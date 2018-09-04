#include<iostream>
using namespace std;

int hold=0;

int fibonacci(int);

int main(){
	int Input;
	cin >> Input ;
	if(Input<1)
		return 0;
	fibonacci(Input);
	cout<<endl;

	return 0;
}

int fibonacci(int N){
	int num;
	if(N>=2){
		num=hold+fibonacci(N-1);
		cout<<num<<" ";
		hold=num-hold;
		return num;
	}
	else {	
		cout<<1<<" ";
		return 1;
	}
}
