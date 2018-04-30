#include<iostream>

using namespace std;

int main(){
	string str="hello world";
	unsigned int pos1=str.find(" ");
	size_t pos2=str.find(" ");

	cout<<"str : "<<str<<endl;
	cout<<"pos1(str.find(" ")) - unsigned int	: "<<pos1<<endl;
	cout<<"pos2(str.find(" ")) - size_t	: "<<pos2<<endl;

	str.erase(0,pos1+1);
	cout<<"\"str.erase(pos+1)\""<<endl;

	cout<<"str : "<<str<<endl;

	pos1=str.find(" ");
	pos2=str.find(" ");
	cout<<"pos1(str.find(" ")) - unsigned int	: "<<pos1<<endl;
	cout<<"pos2(str.find(" ")) - size_t	: "<<pos2<<endl;
	
	cout<<"string::npos : "<<string::npos<<endl;

	return 0;
}

/*
	To use string::npos,
	you shoud use size_t value type.

	[size_t] has much wider scope than [unsigned int]. (64bits OS)

	In 32bits OS, sizeof(unsigned int) == 4
		sizeof(size_t) == 4

	In 64bits OS, sizeof(unsigned int) == 4
		sizeof(size_t) == 8
*/
