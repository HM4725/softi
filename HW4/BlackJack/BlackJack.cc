#include<iostream>
#include<string>
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
		pos=inputs.find(' ');
		cards[i]=inputs.substr(0,pos);
		inputs.erase(0,pos+1);
	}
	cards[number-1]=inputs;

/* J,Q,K를 10으로 변경 */
	for(int i=0; i<number; ++i){
		if(cards[i]=="J"||cards[i]=="Q"||cards[i]=="K"){
			cards[i]+="10";
			cards[i].erase(0,1);
		}
	}

/* 다른 문자가 입력되면 종료, 10보다 큰 수,0 ,1 이 입력되면 종료, 그외에는 합*/
	for(int i=0;i<number; ++i){
		if(cards[i]!="A"){
			if(isdigit(cards[i][0])==false||cards[i]=="0"||cards[i]=="1"||stoi(cards[i])>10){
				delete[] cards;
				return -1;
			}
			else sum+=stoi(cards[i]);
		}
	}

/* A가 1인지 11인지 판별 */
	for(int i=0;i<number; ++i){
		if(cards[i]=="A"){
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

/* 	2 K K. 는 되는데
	2 K K .는 안됨. 마지막 값을 "K "로 인식해버림.

	5 A K 3 을 입력하면 1+10+3으로 인식됨.
	나머지 2개를 다시 입력할 기회를 주지않음.
*/
