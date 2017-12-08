#include<iostream>
#include<stdlib.h>
#include<iomanip>
//include<time.h>	..?? time()?

#define CORRECT true
#define WRONG false

using namespace std;

void MontyHall(int,int&);

enum Strategy {	KEEP=1, CHANGE=2, RANDOM=3 };

int main(){
	int strategy;
	int times;
	int corrects=0;
	cin>>strategy;
	if(strategy!=KEEP&&strategy!=CHANGE&&strategy!=RANDOM) return 0;
	cin>>times;
	if(times<=0) return 0;

	srand(time(NULL));
	int turn=0;
	while(turn++!=times){
		MontyHall(strategy,corrects);
	}

	cout<<fixed<<setprecision(1)<<(double)corrects/times*100<<"% "<<"("<<corrects<<"/"<<times<<")"<<endl;

	return 0;
}

void MontyHall(int _strategy,int& _corrects){
	bool doors[3];	//door0, door1, door2
	const int presentdoor=rand()%3;
	for(int i=0; i<3; i++){
		if(i!=presentdoor) doors[i]=WRONG;
		else doors[i]=CORRECT;	//present
	}
	
	int chosendoor=rand()%3;

again:	//If _starategy==RANDOM, twice. Else, once.
	if(chosendoor==presentdoor){
		if(_strategy==KEEP){
			_corrects++;	/*CORRECT*/
		}
		else if(_strategy==CHANGE){/*WRONG*/}
		else {	//_strategy==RANDOM
			_strategy=(rand()%2)+1;	//KEEP or CHANGE
			goto again;
		}
	}
	else {	//chosendoor!=presentdoor	>>>there are 1correct door and 1wrong door.
		if(_strategy==KEEP){/*WORNG*/}
		else if(_strategy==CHANGE){
			_corrects++;	/*CORRECT*/
		}
		else {	//_strategy==RANDOM
			_strategy=(rand()%2)+1;	//KEEP or CHANGE
			goto again;
		}
	}
}
