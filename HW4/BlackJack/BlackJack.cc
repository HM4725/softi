#include<iostream>

using namespace std;

class Cards{
private:
	int


public:



}

int main(){
	while(true){
		int number(0);
		unsigned int position;
		string inputs;

		cin>>number;
		getline(cin,inputs);
		inputs.erase(0,1);

/* create assigned cards */
		string* cards=new string[number]; 

		for(int i=0; i<number-1 ; ++i){
			position=cards.find(' ');
			cards[i]=inputs.substr(0,position);
			inputs.erase(0,position+1);
		}
		cards[number-1]=inputs;

		

		delete[] cards;		
	}
	return 0;
}
