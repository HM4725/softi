#include<iostream>
#include"reply_admin.h"

ReplyAdmin::ReplyAdmin(){
	chats.push_back("Hello, Reply Administrator!");
	chats.push_back("I will be a good programmer");
	chats.push_back("This class is awesome.");
	chats.push_back("Professor Lim is wise.");
	chats.push_back("Two TAs are kind and helpful.");
	chats.push_back("I think male TA looks cool.");
}
ReplyAdmin::~ReplyAdmin(){}

bool ReplyAdmin::addChat(string _chat){
	chats.push_back(_chat);
	return true;
}

bool ReplyAdmin::removeChat(int _index){
	if(_index>=chats.size()||_index<0) return false;

	list<string>::iterator it=chats.begin();
	for(int i=0; i<_index ; ++i)	it++;
	chats.erase(it);

	return true;
}

bool ReplyAdmin::removeChat(int* _indices, int _count){
	int supple=0;
	bool booleancheck1=false;
	bool booleancheck2=false;
	for (int i=1;i<_count;++i){
		for(int j=0;j<_count-i;j++){
			if(_indices[j]>_indices[j+1]){
				std::swap(_indices[j],_indices[j+1]);
			}
		}
	}
	for (int i=0; i<_count ; ++i){
		booleancheck1=removeChat(_indices[i]-supple);
/*
	this->removeChat(~); 할 필요 없음?
	ReplyAdmin::removeChat(~) 할 필요 없음?
	왜??
*/
		if(booleancheck1) booleancheck2=true;
		supple++;
	}
	return booleancheck2;
}

bool ReplyAdmin::removeChat(int _start, int _end){
	bool booleancheck1=false;
	bool booleancheck2=false;
	if(_start<0) _start=0;
	if(_end>=chats.size()) _end=chats.size()-1;
	for(int i=_start; i<=_end; ++i){
		booleancheck1=removeChat(_start);
		if(booleancheck1) booleancheck2=true;
	}
	return booleancheck2;
}

void ReplyAdmin::printChat(){
	int k=0;
	for(list<string>::iterator it=chats.begin();it!=chats.end(); ++it){
		cout<<k++<<" "<<*it<<endl;
	}
}
