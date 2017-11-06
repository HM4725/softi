#include<iostream>
/* const 부시기 */

class HMC {
private:
	int money;

public:
	HMC(){ money=0; }
	HMC(int _money){ money=_money; }
	void function(int _money);
	void ref_function(int& _money);
	void constref_function(const int& _money);
	int function_const(int _money) const ;
	int ref_function_const(int& _money) const;
	int constref_function_const(const int& _money) const;
//////////////////////////////////////
	void cls_function(HMC _test){
		money=16;
		_test.money=17;
	}
	void clsref_function(HMC& _test){
		money=16;
		_test.money=17;
	}
	void clsconstref_function(const HMC& _test){
		money=16;
		//_test.money=17;	//NO! because of (const HMC&)
	}
	void cls_function_const(HMC _test)const{
		//money=16;	//NO! because of )const
		_test.money=17;
	}
	void clsref_function_const(HMC& _test)const{
		//money=16;	//NO! because of )const
		_test.money=17;
	}
	void clsconstref_function_const(const HMC& _test)const{
		//money=16;	//NO! because of )const
		//_test.money=17;	//NO! because of (const HMC&)
	}
};







void HMC::function(int _money){
	money=_money;
}

void HMC::ref_function(int& _money){
	money=_money;
}

void HMC::constref_function(const int& _money){
	money=_money;
}

int HMC::function_const(int _money)const{
	//money=_money;	
	//NO! 뒤에 const : 멤버 변수 변경 안됨!
	_money++;	//OK!
	return money;
}

int HMC::ref_function_const(int& _money)const{
	//money=_money;
	_money++;	//OK!
	return money;
}	
int HMC::constref_function_const(const int& _money)const{
	//money=_money;
	//_money++;	//NO! because of (const int& )
	return money;
}







int main(){
/* const , refernce , int */

	int x1,y1(7);
	x1=0 ;  //OK!
	int& x2=x1;	//x2 is a alias of x1.
	x2=3 ; //OK! x1=3, x2=3
	x2=y1; //OK! X2에 상수값 7만 들어감, x2=7;이랑 같은의미
	const int& x3=x1;	//x3 is a alias of x3.
		/*x3 has a constant.
		  x3 cannot change the constant.
		  But when change the value of x1,
		  the value of x3 is changed.	*/
//	x3=1 ; //NO! because of const
//	x3=x2; //NO! because of const
	x1=10;	//x3:10	
///////////////////////////////////////

/* const , reference, function */
	HMC test1(10);


	test1.function(x1);
	test1.function(x2);
	test1.function(x3);
	test1.ref_function(x1);
	test1.ref_function(x2);
//	test1.ref_function(x3);	//NO! 
/*binding 'const int' to refernce of type 'int&' discards qualifiers*/
	test1.constref_function(x1);
	test1.constref_function(x2);
	test1.constref_function(x3);
	test1.function_const(x1);
	test1.function_const(x2);
	test1.function_const(x3);
	test1.ref_function_const(x1);
	test1.ref_function_const(x2);
//	test1.ref_function_const(x3);	//NO!
/*binding 'const int' to refernce of type 'int&' discards qualifiers*/
	test1.constref_function_const(x1);
	test1.constref_function_const(x2);
	test1.constref_function_const(x3);

////////////////////////////////////////////////////////
/* class, const, reference, function */

	HMC test2;
	const HMC test3;

	test1.cls_function(test2);
	test1.clsref_function(test2);
	test1.clsconstref_function(test2);
	test1.cls_function(test3);

//	test1.clsref_function(test3);	//NO!
/*binding 'const HMC' to refernce of type 'HMC&' discards qualifiers*/

	test1.clsconstref_function(test3);
	test1.cls_function_const(test2);
	test1.clsref_function_const(test2);
	test1.clsconstref_function_const(test2);
	test1.cls_function_const(test3);
//	test1.clsref_function_const(test3);	//NO!
/*binding 'const HMC' to refernce of type 'HMC&' discards qualifiers*/
	test1.clsconstref_function_const(test3);
	

	return 0;
}
