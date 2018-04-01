#include<iostream>
#include<cstdlib>	//rand()
#include<iomanip>	//decimal point
#include<ctime>	//runtime check
#include<unistd.h>	//usleep()
using namespace std;

int main(){
	clock_t start,end;
	srand(time(NULL)); //rand()의 시드값을 컴퓨터 시간에 맞도록 변경
	int random, purpose;
	cout<<"Input a number from 0 to 9\n>>>";
	cin>>purpose;
	if(purpose<0||purpose>9){
		cout<<"Out of scope!"<<endl;
		return -1;
	}
	start=clock();

	while(true){
		random=rand()%10;
		if(random==purpose){
			cout<<"Got it!"<<endl;
			break;
		}
		usleep(1000);
	}
	end=clock();

	cout<<fixed<<setprecision(4)<<"Runtime:"
		<<(float)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;

	return 0;
}


