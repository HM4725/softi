/* Use a greedy algorithm */
#include<iostream>

#define type8 10won;
#define type7 50won;
#define type6 100won;
#define type5 500won;
#define type4 1000won;
#define type3 5000won;
#define type2 10000won;
#define type1 50000won;


using std::cout;
using std::cin;
using std::endl;

class Change{
private :
	int type_money[8]={50000,10000,5000,1000,500,100,50,10};
		/* c++ 11 standard */
	int type_number[8];

public :
	int money;
	Change(int quant){
		money=quant;
		GleedyAlgorithm();
	}

	void GleedyAlgorithm() {
		for (int i=0;i<8;i++){
			type_number[i]=0;
			while(money>=type_money[i]){
				type_number[i]++;
				money-=type_money[i];
			}
		}
	}
	int* MoneyReturn(){
		return type_money;
	}
	int* NumberReturn(){
		return type_number;
	}
};

int main(){
	int money=1;
	while(money!=0){
		cout<<"Input money you want to change : ";
		cin>>money;
		if(money==0){
			cout<<"quit"<<endl;
			break;
		}
		Change changemoney(money);
		int *pmoney=changemoney.MoneyReturn();
		int *pnumber=changemoney.NumberReturn();
		for(int i=0;i<8;i++){
//			cout<<changemoney.type_money[i]<<"won x "<<
//				changemoney.type_number[i]<<endl;
		/*private*/
			cout<<"*"<<pmoney[i]<<"won X "<<
				pnumber[i]<<endl;
		}
		cout<<"*remainder : "<<changemoney.money<<"won"<<endl;
	}
	return 0;
}
