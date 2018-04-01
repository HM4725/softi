#include<iostream>

class Parameter {
public:
	Parameter(){
		x=0;
		y=0;
		std::cout<<"constructor"<<std::endl;
	}
	/*Parameter(const Parameter& arg){
		x=arg.x;
		y=arg.y;
		std::cout<<"constructor(parameter)"<<std::endl;
	}*/ 
/* 인자가 instance인 constructor 따로 안만들어주면
   constructor 호출 x , 소멸자만 2번 실행 */
	~Parameter(){
		x=0;
		std::cout<<"destructor"<<std::endl;
	}

	void memberfunction(){
		x++;
		y++;
	}
	int x,y;

};

void function(Parameter arg){
	std::cout<<"Begin of function(Parmeter)"<<std::endl;
	std::cout<<"arg.x : "<<arg.x<<" ,arg.y : "<<arg.x<<std::endl;
	std::cout<<"End of function(Parmeter)\n"<<std::endl;
}
/*임시 instance가 새로 생성되므로 생성자,소멸자 생성비용이 든다.
  그러므로 reference를 이용! (생성자,소멸자 생성 x)
*/
void ref_function(Parameter& arg){
	std::cout<<"Begin of ref_function(Parmeter&)"<<std::endl;
	std::cout<<"arg.x : "<<arg.x<<" ,arg.y : "<<arg.x<<std::endl;
	std::cout<<"End of ref_function(Parmeter&)\n"<<std::endl;
}

void constref_function(const Parameter& arg){
	std::cout<<"Begin of function(const Parmeter&)"<<std::endl;
	std::cout<<"arg.x : "<<arg.x<<" ,arg.y : "<<arg.x<<std::endl;
	std::cout<<"Begin of function(const Parmeter&)\n"<<std::endl;
}


int main(){
	Parameter pa;
	pa.memberfunction();

	std::cout<<"pa.x : "<<pa.x<<" ,pa.y : "<<pa.x<<std::endl;

	std::cout<<"fucntion(Pa)"<<std::endl;
	function(pa);
//Parameter arg(pa);
	std::cout<<"ref_fucntion(Pa)"<<std::endl;
	ref_function(pa);
//Parameter& arg(pa);
	std::cout<<"constref_fucntion(Pa)"<<std::endl;
	constref_function(pa);
//const Parameter& arg(pa);
	return 0;
}

/* 
왜 destructor 2번??

function(pa);에서
Parameter arg 임시 instance가 새로 생성되므로
생성자 소멸자가 호출되는데,
인자가 instance인 생성자를 따로 만들어주지 않아
생성자가 호출되지 않았던 것이다.

만약 인자가 instance인 생성자를 따로 만들어주면
생성자와 소멸자가 둘다 호출되는 것을 볼 수 있다.

특정함수에서 인자가 instance인 경우 생성자와
소멸자가 한번 더 호출되는 것을 방지하기 위한
2가지 방법이 있다.

1. 생성자 앞에 explicit 키워드를 써준다.
   컴파일시 이런 문제 발생시 error가 뜨게해 
   미리 방지해준다. (const와 비슷)
2. 특정함수의 인자의 타입으로 &reference나 *pointer를
   사용한다.
	: 위 코드에서 2,3번째 형태.
	: member variable값을 변경하고 싶을 땐 &
	: 읽기만 하고 싶을 땐 const &
*/
