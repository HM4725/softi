#include<iostream>

using namespace std;

int main(){
	int donuts;
	int milk;
	double dpg;

	try{
		cout<<"Enter number of donuts:";
		cin>>donuts;
		cout<<"Enter number of glasses of milk:";
		cin>>milk;

		if(milk<=0)
			throw donuts;

		dpg=donuts/static_cast<double>(milk);
		cout<<donuts<<" donuts.\n"
			<<milk<<" glasses of milk.\n"
			<<"You have "<<dpg
			<<" donuts for each glass of milk.\n";
	}
	catch(int e){
		cout<<e<<" donuts, and No milk!\n"
			<<"Go buy some milk.\n";
	}
	return 0;
}
