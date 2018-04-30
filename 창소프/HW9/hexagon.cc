#include<iostream>
#include<vector>
using namespace std;

int sum;
vector<int> error;

vector<int> hexagon(vector<int>& _vec){
	bool change=false;
	if(_vec[0]==1&&_vec[1]==1&&_vec[2]==1&&_vec[3]==1&&_vec[4]==1&&_vec[5]==1) return _vec;

	for(int i=0; i<6; i++){
		if(_vec[i]>1){
			if(_vec[(i+2)%6]>1){
			sum+=(2*_vec[(i+1)%6]+1);
			_vec[(i+1)%6]++;
			_vec[(i+2)%6]--;
			change=true;
			}
			else if(_vec[(i+3)%6]>1){			
			sum+=(2*_vec[(i+1)%6]+2*_vec[(i+2)%6]);
			_vec[(i+3)%6]--;
			change=true;
			}
			else if(_vec[(i+4)%6]>1){
			sum+=(2*_vec[(i+1)%6]+2*_vec[(i+2)%6]+2*_vec[(i+3)%6]-1);
			_vec[(i+2)%6]--;
			_vec[(i+4)%6]--;
			change=true;
			}
			else if(_vec[(i+5)%6]>1){
			sum+=(2*_vec[(i+1)%6]+2*_vec[(i+2)%6]+2*_vec[(i+3)%6]+2*_vec[(i+3)%6]-2);
			_vec[(i+2)%6]--;
			_vec[(i+3)%6]--;
			_vec[(i+5)%6]--;
			change=true;
			}
			if(change==true)	_vec[i]--;
		}
		if(change==false)	return error;
	}
	return hexagon(_vec);
}
			
			
int main(){
	for(int i=0;i<6;i++)	error.push_back(0);
	int num;
	vector<int> vec;
	vector<int> vtemp;
	cin>>num;
	int temp;
	while(num!=0){
		num--;
		sum=6;
		vec.clear();
		for(int i=0; i<6; i++){
			cin>>temp;
			vec.push_back(temp);
		}
		vtemp=hexagon(vec);
		if(vtemp==error) {
			cout<<"error"<<endl;
			continue;;
		}
		
		cout<<sum<<endl;
	}
	return 0;
}
