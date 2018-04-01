#include <stdio.h>
#include <string>

class Complex;

class Tester{
public:
	double testfunc(Complex& c);
};
/* C++에서는 class와 struct가 거의 동일
 대신 default 차이 :
	class : private ,
	struct : public		*/
struct Complex{
public:
	Complex() : real(0.0),imag(0.0){}
	Complex(double v) : real(v),imag(0.0) {}
	Complex(double r, double i) : real(r), imag(i) {}
	Complex(const Complex& c) : real(c.real), imag(c.imag){}

	Complex& operator=(const Complex& c){ //operator : 재정의
		real=c.real, imag=c.imag;
		return *this;
	} // return valuetype : Complex , Complex& 차이?

	Complex operator+() const {return *this;}
	Complex operator-() const {return Complex(-real,-imag);}

	double& operator[](int i) {
		printf("no const\n");
		return i==0?real:imag;
	}

	const double& operator[] (int i) const {
		printf("const\n");
		return i==0?real:imag;
	}

	void show(std::string sz_prefiex){
		printf("[%s] real: %lf, imag: %lf\n",sz_prefiex.c_str(),real,imag);
	}

private:
	double real, imag;

	friend Complex operator+ (const Complex& lhs, const Complex& rhs);
	friend bool operator< (const Complex& lhs, const Complex& rhs);
//friend : class 밖에서 모두 쓸수 있는 것 -> ok! -> 잘 안쓰임.
	friend double Tester::testfunc(Complex &c);
};

double Tester::testfunc(Complex& c){
	printf("[Tester] %lf, %lf\n", c.real, c.imag);
	return c.real;
}

Complex operator+ (const Complex& lhs, const Complex& rhs){
	return Complex(lhs.real+rhs.real, lhs.imag+rhs.imag);
}
// 이 + 연산자의 대상이 Complex 일때만 해당  :  Complex에 대해서만 정의해줬기 때문
bool operator< (const Complex& lhs, const Complex& rhs){
	return lhs.real<rhs.real && lhs.imag<rhs.imag;
}

/* class에서 함수는 쿼드영역 -> 객체생성시 새로 생기지는 않음.
	변수는 스택영역 -> 객체생성시 계속 새로 생김.
*/

int Test(){
	Complex a(11.0,2.0), b(2.0,5.0), c;
	const Complex cc(33.0,11.0);
	Tester t;

	int n=8;
	//overloading test
	a[n];
	cc[1];

	c=-a;
	c.show("c=a+b");
	(a+b).show("(a+b)");

	//friend test
	t.testfunc(a);

	return 0;
}

int main(){
	Test();

	return 0;
}
