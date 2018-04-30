#include"draw_shape.h"

int main(){
	size_t size_row, size_col;
	cin>>size_row>>size_col;
	Canvas paper(size_row,size_col);

	cin.ignore();	//버퍼 비우기(개행문자)

	while(true){
		string input;
		getline(cin,input);
		if(input.find("add")!=string::npos){
			size_t pos;
			input.erase(0,4);
			pos=input.find(" ");
			if(input.substr(0,pos)=="rect"){
				input.erase(0,5);

				Shape rectangle;
				rectangle.type=RECTANGLE;
				pos=input.find(" ");
				rectangle.x=stoi(input.substr(0,pos));
				input.erase(0,pos+1);
				pos=input.find(" ");
				rectangle.y=stoi(input.substr(0,pos));
				input.erase(0,pos+1);
				pos=input.find(" ");
				rectangle.width=stoi(input.substr(0,pos));
				input.erase(0,pos+1);
				pos=input.find(" ");
				rectangle.height=stoi(input.substr(0,pos));
				input.erase(0,pos+1);
				rectangle.brush=input[0];

				paper.AddShape(rectangle);
				
			}
			else if(input.substr(0,pos)=="tri_up"){
				input.erase(0,7);

				Shape triangle_up;
				triangle_up.type=TRIANGLE_UP;
				pos=input.find(" ");
				triangle_up.x=stoi(input.substr(0,pos));
				input.erase(0,pos+1);
				pos=input.find(" ");
				triangle_up.y=stoi(input.substr(0,pos));
				input.erase(0,pos+1);
				pos=input.find(" ");
				triangle_up.height=stoi(input.substr(0,pos));
				triangle_up.width=2*triangle_up.height-1;
				input.erase(0,pos+1);
				triangle_up.brush=input[0];

				paper.AddShape(triangle_up);
			}
			else if(input.substr(0,pos)=="tri_down"){
				input.erase(0,9);

				Shape triangle_down;
				triangle_down.type=TRIANGLE_DOWN;
				pos=input.find(" ");
				triangle_down.x=stoi(input.substr(0,pos));
				input.erase(0,pos+1);
				pos=input.find(" ");
				triangle_down.y=stoi(input.substr(0,pos));
				input.erase(0,pos+1);
				pos=input.find(" ");
				triangle_down.height=stoi(input.substr(0,pos));
				triangle_down.width=2*triangle_down.height-1;
				input.erase(0,pos+1);
				triangle_down.brush=input[0];

				paper.AddShape(triangle_down);
			}
			else {
				cout<<"Input again, correctly.\n";
			}
		}
		else if(input.find("delete")!=string::npos){
			input.erase(0,7);
			int dltindex;
			dltindex=stoi(input);

			paper.DeleteShape(dltindex);
		}
		else if(input=="draw"){
			paper.Draw(cout);
		}
		else if(input=="dump"){
			paper.Dump(cout);
		}
		else if(input=="quit"){
			break;
		}
		else {
			cout<<"Input again, correctly.\n";
		}
	}
	return 0;
}
