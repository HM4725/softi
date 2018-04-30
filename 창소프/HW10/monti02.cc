#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<ctime>
#define CORRECT true
#define WRONG false

using namespace std;

void MontyHall(int,int,int&);

enum Strategy {	KEEP=1, CHANGE=2, RANDOM=3 };

int main(){
	clock_t start,end;
	int strategy,times,doors_num;
	int corrects=0;
	cin>>strategy;
	if(strategy!=KEEP&&strategy!=CHANGE&&strategy!=RANDOM) return 0;
	cin>>times;
	if(times<=0) return 0;
	cin>>doors_num;
	if(doors_num<=2||doors_num>=100) return 0;

	srand(time(NULL));
	
	start=clock();
	int turn=0;
	while(turn++!=times){
		MontyHall(strategy,doors_num,corrects);
	}

	cout<<fixed<<setprecision(1)<<(double)corrects/times*100<<"% "<<"("<<corrects<<"/"<<times<<")"<<endl;

	end=clock();
	cout<<fixed<<setprecision(4)<<"Runtime:"<<(float)(end-start)/CLOCKS_PER_SEC<<"sec"<<endl;
	return 0;
}

void MontyHall(int _strategy,int _num,int& _corrects){
	vector<bool> doors;
	doors.resize(_num);
	//door[0], door[1], door[2], ..., door[_num-1]
	int presentdoor=rand()%_num;
	for(int i=0; i<_num; i++){
		if(i!=presentdoor) doors[i]=WRONG;
		else doors[i]=CORRECT;	//present
	}
	
	int chosendoor=rand()%_num;

	if(chosendoor==presentdoor){
		if(_strategy==RANDOM){ _strategy=(rand()%2)+1; }
		if(_strategy==KEEP){ _corrects++; }
		/*_else if(strategy==CHANGE) choose a wrong door*/
	}
	else {	//chosendoor!=presentdoor
		if(_strategy==RANDOM){ _strategy=(rand()%2)+1; }
		if(_strategy==CHANGE){
			doors.erase(doors.begin()+chosendoor);
			_num--;			//except the chosendoor
			for(vector<bool>::iterator itr=doors.begin();itr!=doors.end();itr++){
				if(*itr==WRONG){
					doors.erase(itr);
					_num--;
					break;
				}
			}	//Monty opens a wrong door.
			int changedoor=rand()%_num;
			if(doors[changedoor]==CORRECT) {_corrects++;}
			/*if(doors[changedoor]==WRONG) choose a wrong door; */
		}
		/* else if(_strategy==KEEP) choose a wrong door */
	}
}
