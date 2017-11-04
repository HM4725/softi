#include<iostream>
#include<vector>
using namespace std;

int main(){
	vector<int> myVec;

	if(myVec.empty()) cout <<"My vector is empty"<<endl;

	for (int i=1; i<=5 ; ++i)
		myVec.push_back(i);
// 1 2 3 4 5


	cout<<"Size of my vector is "<<myVec.size()<<endl;

	for(int i=6; i<=10; ++i)
		myVec.push_back(i);
// 1 2 3 4 5 6 7 8 9 10

	cout<<"Size of my vector is "<<myVec.size()<<endl;

	if(!myVec.empty()) cout<<"My Vector is NOT empty"<<endl;

	cout<<"My Vetor contains : ";
	for(vector<int>::iterator it=myVec.begin() ; it!=myVec.end();++it)
		cout<<' '<<*it;
	cout<<'\n';

	for ( int i=0; i<10; ++i)
		cout<<"vector at position "<<i<<" is "//<<myVec.at(i)<<endl;
							<<myVec[i]<<endl;
	cout<<'\n';

	myVec.erase(myVec.begin()+5);
// 1 2 3 4 5 7 8 9 10
	cout<<"////////////////\n";

	cout<<"My Vetor contains : ";
	for(vector<int>::iterator it=myVec.begin() ; it!=myVec.end();++it)
		cout<<' '<<*it;
	cout<<'\n';
	

	myVec.erase(myVec.begin(),myVec.begin()+3);
// 5 7 8 9 10

	cout<<"My Vetor contains : ";
	for(vector<int>::iterator it=myVec.begin() ; it!=myVec.end();++it)
		cout<<' '<<*it;
	cout<<'\n';

	cout<<"////////////////\n";
	vector<int>::iterator it;
	it=myVec.end();
	it--;
	cout<<*it<<endl;
	myVec.clear();
//
	if(myVec.empty()) cout<<"My vector is empty."<<endl;

	return 0;

}
