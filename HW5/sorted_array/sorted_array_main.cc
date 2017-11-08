#include"sorted_array.h"

int main(){
	size_t pos;
	string input;
	SortedArray array;
	bool arrayset=false;
	while(true){
		getline(cin,input);
		if(isdigit(input[0])){
			pos=0;
			while(pos!=string::npos){
				pos=input.find(" ");
				if(isdigit(input[0]))
					array.AddNumber(stoi(input.substr(0,pos)));
				input.erase(0,pos+1);
			}
			arrayset=true;
		}
		else if(input=="ascend"&&arrayset){
			vector<int> ascend=array.GetSortedAscending();
			for(vector<int>::iterator itr=ascend.begin();itr!=ascend.end();++itr){
				cout<<*itr<<" ";
			}
			cout<<endl;
		}
		else if(input=="descend"&&arrayset){
			vector<int> descend=array.GetSortedDescending();
			for(vector<int>::iterator itr=descend.begin();itr!=descend.end();++itr){
				cout<<*itr<<" ";
			}
			cout<<endl;
		}
		else if(input=="max"&&arrayset){
			cout<<array.GetMax()<<endl;
		}
		else if(input=="min"&&arrayset){
			cout<<array.GetMin()<<endl;
		}
		else if(input=="quit"){
			break;
		}
		else cout<<"Input again"<<endl;
	}
	return 0;
}
