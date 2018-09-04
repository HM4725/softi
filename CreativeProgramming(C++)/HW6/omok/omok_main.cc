#include"omok.h"
using namespace std;

int main(){
	Omok game;
	int winner=NOBODY;
	int play_turn=0;

	while(true){
		int x, y, check;
		cin>>x>>y;

		check=game.Put(x,y);

		if(check==NOBODY){
			cout<<"Can not be placed there"<<endl;
			continue;
		}

		game.IsOmok(&winner);
	cout<<game;

		if(winner!=NOBODY)	break;

		play_turn++;
		if(play_turn==GROUND_SIZE*GROUND_SIZE)	break;

	}
	

	if(winner==WHITE){
		cout<<"Winner: White player"<<endl;
	}
	else if(winner==BLACK){
		cout<<"Winner: Black plyaer"<<endl;
	}
	else	{
		cout<<"Draw"<<endl;
	}

	return 0;
}
