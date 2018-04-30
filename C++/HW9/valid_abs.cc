#include<iostream>
#include<vector>
using namespace std;

bool VABScheck(string);

int main(){
	int times;
	vector<string> svec;
	string tstr;
	cin>>times;
	svec.resize(times);
	for(vector<string>::iterator itr=svec.begin();itr!=svec.end();itr++){
		cin>>tstr;
		*itr=tstr;
	}
	for(vector<string>::iterator itr=svec.begin();itr!=svec.end();itr++){
		if(VABScheck(*itr))	cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}

bool VABScheck(string str){
	size_t pos;
	while(true){
		pos=str.find("<>");
		if(pos!=string::npos){
			str.erase(pos,2);
		}
		else break;
	}
	return str.empty()?true:false;
}
