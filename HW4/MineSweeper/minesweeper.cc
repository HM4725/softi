#include"minesweeper.h"
#define MINE 5879

Minesweeper::Minesweeper(){
	mwidth=0;
	mheight=0;
	touchcount=0;
	startplay=false;
	setmap=false;
	dead=false;
}

Minesweeper::~Minesweeper(){
	startplay=false;
	setmap=false;
	dead=false;
	map.clear();
	number_map.clear();
}

bool Minesweeper::setMap(size_t _width, size_t _height, vector<string>& _map){

/*default for setting again*/
	startplay=false;
	setmap=false;
	map.clear();
	number_map.clear();
	mwidth=_width;
	mheight=_height;

/*error prevention*/
	if(_width==0||_height==0){
		cout<<"The arguments are out of scope!\n"<<endl;
		mwidth=0;
		mheight=0;
		return false;
	}
	for (size_t i=0; i<mheight; ++i){
		for(size_t j=0; j<mwidth; ++j){
			if(_map[i][j]!='.'&&_map[i][j]!='*'){
				cout<<"You set the map wrongly! Set again.\n"<<endl;
				mwidth=0;
				mheight=0;
				return false;
			}
		}
	}
	for(size_t i=0; i<mheight; ++i){
		if(_map[i].size()!=mwidth){	// sizeof vs .size()
			cout<<"You set the map wrongly! Set again.\n"<<endl;
			mwidth=0;
			mheight=0;
			return false;
		}
	}

/*set the map*/
	for(size_t i=0; i<mheight; ++i){
		map.push_back(_map[i]);
	}
	
/*set the number_map*/
	number_map.resize(mheight);
	for(size_t i=0; i<number_map.size();++i)
		number_map[i].resize(mwidth,0);



	for(int i=0; i<(signed)mheight; ++i){
		for(int j=0; j<(signed)mwidth; j++){
			if(map[i][j]=='*') number_map[i][j]=MINE;
			else {
				for(int map_y=i-1;map_y<=i+1;map_y++){
					for(int map_x=j-1;map_x<=j+1;map_x++){
						if(map_y>=0&&map_y<(signed)mheight&&map_x>=0&&map_x<(signed)mwidth&&map[map_y][map_x]=='*')
							number_map[i][j]++;
					}
				}				
			}
		}
	}
	setmap=true;

	printMap_set();
	return setmap;
}

bool Minesweeper::toggleMine(int _x, int _y){

/*error prevention*/
	if(startplay==true){
		cout<<"Minesweeper is in the playing mode.\n"<<endl;
		return false;
	}
	else if(setmap==false){
		cout<<"Before toggling, you have to set the map.\n"<<endl;
		return false;
	}
	else if(_x<0||_x>=(signed)mwidth||_y<0||_y>=(signed)mheight){
		cout<<"The arguments are out of scope.\n"<<endl;
		return false;
	}

/*toggle*/
	if(get(_x,_y)=='.'){
		map[_y][_x]='*';
		number_map[_y][_x]=MINE;
		for(int i=_y-1;i<=_y+1;i++){
			for(int j=_x-1;j<=_x+1;j++){
				if(i>=0&&i<(signed)mheight&&j>=0&&j<(signed)mwidth&&map[i][j]!='*')
					number_map[i][j]++;
			}
		}				
	}
	else {	//when map[_y][_x]=='*'
		number_map[_y][_x]=0;
		for(int i=_y-1;i<=_y+1;i++){
			for(int j=_x-1;j<=_x+1;j++){
				if(i>=0&&i<(signed)mheight&&j>=0&&j<(signed)mwidth&&map[i][j]=='*')
					number_map[_y][_x]++;
			}
		}
		number_map[_y][_x]--; //because of when i=_y and j=_x

		for(int i=_y-1;i<=_y+1;i++){
			for(int j=_x-1;j<=_x+1;j++){
				if(i>=0&&i<(signed)mheight&&j>=0&&j<(signed)mwidth&&map[i][j]!='*')
					number_map[i][j]--;
			}
		}
		map[_y][_x]='.';
	}

	printMap_set();

	return true;
}

size_t Minesweeper::width() const {
	return mwidth;
}

size_t Minesweeper::height() const {
	return mheight;
}

char Minesweeper::get(int _x, int _y) const{
	if(_x>=0&&_x<(signed)mwidth&&_y>=0&&_y<(signed)mheight)
		return map[_y][_x];
	else return ' ';
}

bool Minesweeper::setPlay(){

/*error prevention*/
	if(setmap==false){
		cout<<"Before playing, you have to set a map.\n"<<endl;
		return false;
	}
	if(startplay==true&&dead==false) {
		cout<<"You are already playing!\n"<<endl;
		return false;
	}

	touchcount=0;
	startplay=true;
	dead=false;

/* The map is marked with '_' */
	for(size_t i=0; i<mheight; ++i){
		for(size_t j=0; j<mwidth; ++j){
			map[i][j]='_';
		}
	}

	printMap();

	return true;
}

bool Minesweeper::touchMap(int _x, int _y){
	if(startplay==false&&setmap==false){
		cout<<"Before touching, you have to set a map.\n"<<endl;
		return false;
	}
	else if(dead==true||startplay==false){
		cout<<"Before touching, you have to play game.\n"<<endl;
		return false;
	}
	if(_x<0||_x>=(signed)mwidth||_y<0||_y>=(signed)mheight){
		cout<<"The arguments are out of scope.\n"<<endl;
		return false;
	}

	touchcount++;

	if(number_map[_y][_x]==MINE){
		cout<<"DEAD("<<touchcount<<")\n"<<endl;
		dead=true;
		return true;
	}
	else	{
		map[_y][_x]=(char)number_map[_y][_x]+48;
		printMap();

		return true;
	}
}

int Minesweeper::touchCount() const{
	return touchcount;
}

void Minesweeper::printMap_set(){
	for(size_t i=0; i<mheight; i++){
		for(size_t j=0; j<mwidth; j++){
			if(number_map[i][j]==MINE) cout<<'*';
			else cout<<number_map[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}

void Minesweeper::printMap(){
	for(size_t i=0; i<mheight; i++){
		for(size_t j=0; j<mwidth; j++){
			cout<<get(j,i);
		}
		cout<<endl;
	}
	cout<<endl;
}
