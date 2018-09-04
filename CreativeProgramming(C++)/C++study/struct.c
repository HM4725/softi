#include<stdio.h>

////////////////////////////////제작자코드
struct userdata{
	int nAge;
	char szName[32];
	void(*Print)(struct userdata *);
};
void PrintUserData(struct userdata *pUser){
	printf("%d, %s\n", pUser->nAge,pUser->szName);
}

////////////////////////////////사용자코드

int main(){
	struct userdata hm={20,"LEE",PrintUserData};

	//출력
	//1
	printf("%d,%s\n",hm.nAge,hm.szName);
	//2
	PrintUserData(&hm);
	//3
	hm.Print(&hm);//--> C style
	//4
//	hm.Print();	--> C++ style

	return 0;
}


/*
C : struct  --> function: only declaration
C++ : class  --> definition, too.
*/
