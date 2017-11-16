#include"point2d.h"
#include<iostream>
#include<vector>

int main(){
	vector<Point> vectors;

	while(true){
		string command;
		getline(cin,command);

		if(command.find("set")!=string::npos){
			command.erase(0,4);
			char tname=command[0];
			size_t pos;
			int tx,ty;
			command.erase(0,2);
			pos=command.find(" ");
			tx=stoi(command.substr(0,pos));
			command.erase(0,pos+1);
			ty=stoi(command);

			Point temp(tx,ty);
			temp.name=tname;
			vectors.push_back(temp);

			cout<<vectors[0].name<<endl;
		}

		else if(command.find("eval")!=string::npos){
			command.erase(0,5);
			char oper;
			string tl,tr;
			size_t pos;
			pos=command.find(" ");
			tl=command.substr(0,pos);
			command.erase(0,pos+1);
			oper=command[0];
			command.erase(0,2);
			tr=command;

			Point* ltemp=NULL;
			Point* rtemp=NULL;

			if(isdigit(tl[0])){
				ltemp=new Point(stoi(tl));
			}
			else	{
				vector<Point>::iterator itr;
				for(itr=vectors.begin();itr!=vectors.end();itr++){
					if((*itr).name==tl[0])	break;
				}

				if(itr==vectors.end()){
					cout<<"input error"<<endl;
					continue;
				}
				else	{
					ltemp=new Point(*itr);
				}
			}


			if(isdigit(tr[0])){
				rtemp=new Point(stoi(tr));
			}
			else	{
				vector<Point>::iterator itr;
				for(itr=vectors.begin();itr!=vectors.end();itr++){
					if((*itr).name==tr[0])	break;
				}

				if(itr==vectors.end()){
					cout<<"input error"<<endl;
					continue;
				}
				else	{
					rtemp=new Point(*itr);
				}
			}



			if(oper=='+'){
				cout<<"("<<(*ltemp+*rtemp).x_<<","<<(*ltemp+*rtemp).y_<<")\n";
			}
			else if(oper=='-'){
				cout<<"("<<(*ltemp-*rtemp).x_<<","<<(*ltemp-*rtemp).y_<<")\n";
			}
			else if(oper=='*'){
				cout<<"("<<((*ltemp)*(*rtemp)).x_<<","<<((*ltemp)*(*rtemp)).y_<<")\n";
			}

			if(ltemp!=NULL)	delete ltemp;
			if(rtemp!=NULL) delete rtemp;

		}

		else if(command.find("quit")!=string::npos){
			break;
		}

		else	{
			cout<<"input error"<<endl;
		}
	}
	return 0;
}
