#include"reply_admin.h"

ReplyAdmin::ReplyAdmin(){
	chats = new string[NUM_OF_CHAT];
	/* 	ReplyAdmin Class 에서 이미 string* chats 할당을 
	해주었으므로 Constructor에서 또 string* chats 할당을
	해줄 필요가 없음. 이렇게 동적할당,변수선언을 또 해주면
	같은 이름의 변수가 2개 생기므로 1개는 unused variable로
	간주되고 프로그램이 원하는대로 실행되지 않음.
	-> 변수선언은 1번만!!
	처음에는 string* chats= new string[NUM_OF_CHAT]라고 썼음
	메모리 할당 오류가 뜸. 세그멘테이션 오류(core dumped)
	class 안에서는 int num; 이렇게 해주고
	constructor 안에서는 num=10; 이렇게 해주는 것과 같음*/
	addChat("Hello, Reply Administrator!");
	addChat("I will be a good programmer.");
	addChat("This class is awesome.");
	addChat("Professor Lim is wise.");
	addChat("Two TAs are kind and helpful.");
	addChat("I think male TA looks cool.");
}

ReplyAdmin::~ReplyAdmin(){
	delete [] chats;
}

int ReplyAdmin::getChatCount(){
	int i;
	for(i=0;i<NUM_OF_CHAT;i++){
		string s=chats[i]; //problem-->clear
		if(s.empty()==true) break;
	}
	return i;
}

bool ReplyAdmin::addChat(string _chat){
	int count=this->getChatCount();  // problem-->clear
	this->chats[count]=_chat;
	if(this->chats[count]==_chat)
		return true;
	else return false;
}

bool ReplyAdmin::removeChat(int _index){
	int count=this->getChatCount();
	if(_index<0||_index>=count)
		return false;
	for(int i=_index;i<count-1;++i){
		this->chats[i]=this->chats[i+1];
	}
	chats[count-1]="";
	return true;
}

bool ReplyAdmin::removeChat(int* _indices, int _count){
	int hold,supple(0);
	bool boolean1=false,boolean2=false;
	if(_indices==NULL)/* there is no _indices */
		return boolean2;
	/* Integer Sort of _indices */
	for(int i=1;i<_count;++i){	
		for(int j=0;j<_count-i;++j){
			if(_indices[j]>_indices[j+1]){
				hold=_indices[j];
				_indices[j]=_indices[j+1];
				_indices[j+1]=hold;
			}
		}
	}
	/* remove chat */
	for(int i=0;i<_count;++i){
		boolean1=this->removeChat(_indices[i]-supple);
		if(boolean1) {
			supple++;
			boolean2=true; 
		}
	}
	return boolean2; /* 하나라도 삭제 성공시 true 리턴 */
}

bool ReplyAdmin::removeChat(int _start, int _end){
	bool boolean1=false,boolean2=false;
	for(int i=_start ; i<=_end ; i++){
		boolean1=this->removeChat(_start);
		if(boolean1)
			boolean2=true;
		else _start++;
	}
	return boolean2;
}

void ReplyAdmin::printChat(){
	int count=this->getChatCount();
	for(int i=0; i<count; ++i)
		cout<<i<<" "<<this->chats[i]<<endl;
}

/* 보완

1. #remove -1-3 (start<0 case) : 1~3이 지워짐
2. #remove 3-1 (start>end case) : 1이 지워짐
	--> skeleton code(reply_admin_main.cc) logic error

*/
