#include<iostream>
#include<string>
#include<stdio.h>

using namespace std;

const int NUM_OF_CHAT=200;

int getChatCount(string *_chatList){
	int i;
	for(i=0;i<NUM_OF_CHAT; i++){
		string s=_chatList[i];
		if(s.empty()==true) break;
	}
	return i;
}

void printChat(string *_chatList){
	int count=getChatCount(_chatList);
	for(int i=0; i<count; ++i){
		cout<<i<<" "<<_chatList[i]<<endl;
	}
}

bool addChat(string *_chatList, string _chat){
	int count=getChatCount(_chatList);
	_chatList[count]=_chat;
	return true;
}
bool removeChat(string *_chatList, int _index){
	int count=getChatCount(_chatList);
	for(int i=_index; i<count-1;i++){
		_chatList[i]=_chatList[i+1];
	}
	_chatList[count-1]="";
	return true;
} 

int main(void){
	string *chats=new string[NUM_OF_CHAT];

	addChat(chats,"Hello, Relpy Administrator!");
	addChat(chats,"I will be a good programmer.");
	addChat(chats,"This class is awesome.");
	addChat(chats,"Professor Lim is wise.");
	addChat(chats,"Two TAs are kind and helpful.");
	addChat(chats,"I think TAs look cool.");

	while(true){
		string command;
		getline(cin,command);
		
		if(command.find("#quit")==0) break;
		else if(command.find("#remove")!=string::npos){
			bool result=false;
			string s_index=command.substr(8);
			
			if(s_index.find(",")!=string::npos){
				int num,comma,hold,k=0,t=0;
				char* remainder=new char[s_index.size()];
				int* Narray=new int[k+1];

	/*#remove ~,~,~ (string)에서 ~(int)를 추출 */
				while(true){
					sscanf(s_index.c_str(),"%d,%s",&num,remainder);
					comma=s_index.find(",");
					s_index=s_index.substr(comma+1);
					Narray[t++]=num;
					
					if(s_index.find(",")==string::npos)
						break;
				}
				sscanf(s_index.c_str(),"%d",&num);
				Narray[t]=num;
	/* int를 오름차순으로 정렬 */
				for(int i=0;i<t;i++){
					for(int j=0;j<t-i;j++){
						if(Narray[j]>Narray[j+1]){
							hold=Narray[j];
							Narray[j]=Narray[j+1];
							Narray[j+1]=hold;
						}

					}
				}
	/* int값대로 제거 */
				for(int i=0;i<=t;i++){
					if(Narray[i]-k>=getChatCount(chats)||Narray[i]-k<0)
						continue;
					result=removeChat(chats,Narray[i]-k++);
				}
				delete [] remainder;
				delete [] Narray;
			}
			else if(s_index.find("-")!=string::npos){
				int fnum,lnum;
				sscanf(s_index.c_str(),"%d-%d",&fnum,&lnum);
				if(fnum<0||lnum<0)
					continue;
				if(lnum>=getChatCount(chats))
					lnum=getChatCount(chats)-1;
				for(int i=fnum;i<=lnum;i++)
					result=removeChat(chats,fnum);
			}
			else {
				int num;
				sscanf(s_index.c_str(),"%d",&num);
				if(num<getChatCount(chats)&&num>=0)
					result=removeChat(chats,num);
			}
			if(result)
				printChat(chats);
		}
		else if(addChat(chats,command))
			printChat(chats);
	}

	delete[] chats;

	return 0;
}
