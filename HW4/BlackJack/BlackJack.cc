#include<iostream>
#include<string>
#define LESSCARD 4294967295

using namespace std;

int BlackJack(){
	int number,sum=0;
	unsigned int pos;
	string inputs;
	
	cin>>number;
	getline(cin,inputs);
	inputs.erase(0,1);

	if(number<2) return -1;
	/* number가 정수가 아닐때,
		2보다 작은 정수일 때 : return -1; */
	string* cards=new string[number];

/* inputs을 각 카드값로 나눔 */
	for(int i=0; i<number-1 ; ++i){
		pos=inputs.find(" ");

		if(pos==LESSCARD){
			delete[] cards;
			return -1;
		}			// 카드가 number 이하로 입력 되었을 때 종료
		cards[i]=inputs.substr(0,pos);
		inputs.erase(0,pos+1);
	}
	cards[number-1]=inputs;

/* J,Q,K를 10으로 변경 */
	for(int i=0; i<number; ++i){
		if(cards[i].size()>=3){
			delete[] cards;
			return -1;
		}			// 카드가 number 이상으로 입력 되었을 때 종료

		if(cards[i][0]=='J'||cards[i][0]=='Q'||cards[i][0]=='K'){
			cards[i].erase();
			cards[i]+="10";
		}
	}

/* 다른 문자가 입력되면 종료, 10보다 큰 수,0 ,1 이 입력되면 종료, 그외에는 합*/
	for(int i=0;i<number; ++i){
		if(cards[i][0]!='A'){
			if(isdigit(cards[i][0])==false||stoi(cards[i])==0||stoi(cards[i])==1||stoi(cards[i])>10){
				delete[] cards;
				return -1;
			}
			else sum+=stoi(cards[i]);
		}
	}



/* A가 1인지 11인지 판별 */
	for(int i=0;i<number; ++i){
		if(cards[i][0]=='A'){
			if(sum>=0&&sum<11) sum+=11;	
			else sum+=1;
		}
	}

	delete[] cards;

	return (sum>21) ? 0 : sum ;

}

int main(){
	int result;
	while(result!=-1){
		result=BlackJack();
		if (result<21&&result>0)	cout<<result<<endl;
		else if(result==21)	cout<<"BlackJack"<<endl;
		else if(result==0)	cout<<"Exceed"<<endl;
	}

	return 0;
}
