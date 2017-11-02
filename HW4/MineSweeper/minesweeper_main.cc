#include"minesweeper.h"

int main(){
	Minesweeper minesweeper;
	while(true){
		string command;
		getline(cin,command);

		if (command.find(":set")!=string::npos){
			if(command==":set") continue;

			size_t pos,width,height;
			vector<string> inputs;
			string row_input;

		/* :set width height */
			command.erase(0,5);
			pos=command.find(" ");

			if(command[0]=='-'){
				cout<<"The arguements are out of scope!\n"<<endl;
				inputs.clear();
				continue;
			}	// Prevent when width<0

			width=stoi(command.substr(0,pos));
			command.erase(0,pos+1);

			if(command[0]=='-'){
				cout<<"The arguements are out of scope!\n"<<endl;
				inputs.clear();
				continue;
			}	// Prevent when height<0

			height=stoi(command);

		/* input temporary map */
			for(size_t i=0; i<height ; ++i){
				cin>>row_input;
				inputs.push_back(row_input);
			}
		/* set map */
			cout<<endl;
			minesweeper.setMap(width,height,inputs );
			inputs.clear();
		}


		else if(command.find(":toggle")!=string::npos){
			if(command==":toggle") continue;

			int x,y;
			size_t pos;	

		/* :toggle x y */
			command.erase(0,8);
			pos=command.find(" ");
			x=stoi(command.substr(0,pos));
			command.erase(0,pos+1);
			y=stoi(command);
			
		/* toggle */
			minesweeper.toggleMine(x,y);
		}


		else if(command.find(":play")!=string::npos){
			minesweeper.setPlay();
		}


		else if(command.find(":touch")!=string::npos){
			if(command==":touch") continue;

			int x,y;
			size_t pos;	

		/* :touch x y */
			command.erase(0,7);
			pos=command.find(" ");
			x=stoi(command.substr(0,pos));
			command.erase(0,pos+1);
			y=stoi(command);
			
		/* touch */
			minesweeper.touchMap(x,y);
		}


		else if(command.find(":quit")!=string::npos){
			break;
		}

	}
	return 0;
}
