#include<iostream>
#include<vector>
using namespace std;

int Tn(int);
int iTn(int);
bool isSumTri(int);

int main(){
	int times;
	vector<int> Numbers;
	cin>>times;
	Numbers.resize(times);
	for(vector<int>::iterator itr=Numbers.begin();itr!=Numbers.end();itr++){
		cin>>*itr;
		if(*itr<3||*itr>1000) return 0;
	}
	for(vector<int>::iterator itr=Numbers.begin();itr!=Numbers.end();itr++){
		if(isSumTri(*itr))	cout<<1<<endl;
		else cout<<0<<endl;
	}
	return 0;
}

int Tn(int num){
	return num*(num+1)/2;
}
int iTn(int _Tn){
	int num=1;
	while(Tn(num)<_Tn){
		num++;
	}
	return num-1;	//_Tn<=0 : 0, _Tn==0 : 0
}
bool isSumTri(int num){	//3<=num<=1000
	vector<int> TriNums;
	int max=0;
	if(max<iTn(num)) max=iTn(num);
	TriNums.resize(max);
	for(int i=1; i<=max; i++){
		TriNums[i-1]=Tn(i);
	}
	for(vector<int>::iterator itr1=TriNums.begin();itr1!=TriNums.end();itr1++){
		for(vector<int>::iterator itr2=TriNums.begin();itr2!=TriNums.end();itr2++){
			for(vector<int>::iterator itr3=TriNums.begin();itr3!=TriNums.end();itr3++){
				if(num==*itr1+*itr2+*itr3)	return true;
			}
		}
	}
	return false;
}
