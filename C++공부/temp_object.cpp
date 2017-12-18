#include<iostream>
using namespace std;

class Temp{
	public:
		Temp(){
			cout<<"Temp"<<endl;
			number=0;
		}
		Temp(int num){ 
			cout<<"Temp("<<num<<")"<<endl;
			number=num;
		}
		Temp(const Temp& t){
			cout<<"Temp(Temp)"<<endl;
			number=t.number;
		}
////////////////////////////
		~Temp(){
			if(number==0){
				cout<<"~Temp(0).default"<<endl;
			}
			else {
				cout<<"~Temp("<<number<<")\n";
			}
		}
////////////////////////////
		Temp operator=(const Temp& C){
			number=C.number;
			return *this;
		}
		Temp operator+(const Temp& B) const {
			return Temp(this->number+B.number);
		}	/* B에 instance가 들어가면 생성자호출 x
			   integer가 들어가면 생성자호출 o */
	private:
		int number;
};		//클래스내의 함수에서 인자를 인스턴스 참조형으로 받을 때
		//const instance& 처럼 const를 써야 컴파일이 됨.
/*Temp operator+(const Temp& lhs, const Temp& rhs){
	return Temp(lhs.number+rhs.number);
}*/	// class외부에서 private변수를 접근불가

/*int operator+(int a, int b){
	cout<<"operator+ called!"<<endl;
	return a+b;
}*/ // class, enum type이 아닌 변수에 대한 operator overloading은 허용X 
//////////////////////////////
int main(){
	cout<<"Temp A(3) : ";	//Temp A(3) : Temp(3)
	Temp A(3);
	cout<<"Temp B(5) : ";	//Temp B(5) : Temp(5)
	Temp B(5);
	cout<<"Temp C : ";		//Temp C : Temp
	Temp C;
	cout<<"C=A+B : " ;		//C=A+B : Temp(8)	//임시객체
							//Temp(Temp)	//임시객체
	C=A+B;					//~Temp(8,8)	//임시객체
//	C.operator=(A.operator+(B));	// =, +를 함수처럼 사용할 수 있음.
	cout<<"End of main()\n";
	return 0;				//~Temp(8,5,8) C,B,A order
}


/*	1. 디폴트 생성자 (매개변수 0개)
	2. 변환 생성자 (매개변수 1개)
	3. 다중 생성자 (매개변수 여러개)
	4. 복사 생성자 (매개변수 = 클래스 , deep copy )
	5. 이동 생성자 (매개변수 = 클래서 , r-value 참조 , swallow copy , c++11 )
		비용 : 복사생성자 > 이동생성자
		성능 : 복사생성자 < 이동생성자
 */

