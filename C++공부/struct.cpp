#include<iostream>

/////////////////////////////////제작자코드
struct USERDATA{
	int nAge;
	char szName[32];
	
	void Print(USERDATA *pUser){
		std::cout<<pUser->nAge<<", "<<pUser->szName<<std::endl;
	}
	void Print2(){
		std::cout<<this->nAge<<", "<<this->szName<<std::endl;
	}
};

/////////////////////////////////사용자코드
int main(){	
	USERDATA hm={20,"LEE"};

	hm.Print(&hm);
	hm.Print2();



	return 0;
}
