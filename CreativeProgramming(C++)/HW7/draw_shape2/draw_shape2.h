#ifndef __draw_shape_2__
#define __draw_shape_2__

#include<vector>
#include<iostream>
using namespace std;

class Canvas {
	public:
		Canvas(size_t row, size_t col);
		~Canvas();

		// canvas 크기를 w * h 로 변경한다. 그려진 내용은 보존한다.
		void Resize (size_t w, size_t h);

		// (x, y) 위치에 문자를 그린다. 범위 밖의 x, y는 무시한다.
		bool Draw(int x, int y, char brush);

		// 그려진 내용을 모두 지운다. (‘.’으로 초기화)
		void Clear();

		size_t row() const { return row_; }
		size_t col() const { return col_; }
		vector<vector<char> >& canvas() const { return ref_canvas; } 
	private:
		// 그려진 모양을 저장할 수 있도록 데이터멤버를 정의 (resize 가능에 주의)
		friend ostream& operator<<(ostream& os, const Canvas& c);

		size_t row_,col_;
		vector<vector<char> > canvas_;
		vector<vector<char> >& ref_canvas=canvas_;
};

class Shape {
	public:
		virtual ~Shape();	//why?
		virtual void Draw(Canvas* canvas) const = 0;	//abstract class
		int x() const { return x_; }
		/*C++에선 멤버함수와 멤버변수 명이 서로 달라야함.
		  java에선 같아도 상관없음	*/
		int y() const { return y_; }
		int h() const { return h_; }
		int w() const { return w_; }
		char brush() const { return brush_; }
		string type() const { return type_; }
		void InputVar(int x,int y,int h,char brush);
/* 질문 : w()를 derived class에 쓰면
   base class에서 w이름을 가진 멤버가 없다고 나옴 
   --> cast를 해야한다고 함.
   그렇다면 base class에선 어떻게 derived class의 함수를 
   사용하는 것? */
	protected:
		int x_,y_,h_,w_;
		char brush_;
		string type_;
};


class Rectangle :public Shape{
	public:
		Rectangle(){
			type_="rect";	//상속받은 클래스의 멤버?!
		}
		void Draw(Canvas* canvas) const;
		void Inputw(int w);
	private:
};

class UpTriangle :public Shape{
	public:
		UpTriangle(){
			type_="tri_up";
		}
		void Draw(Canvas* canvas) const;
	private:

};

class DownTriangle :public Shape{
	public:
		DownTriangle(){
			type_="tri_down";
		}
		void Draw(Canvas* canvas) const;
	private:
};
class Diamond :public Shape{
	public:
		Diamond(){
			type_="diamond";
		}
		void Draw(Canvas* canvas) const;
	private:
};

istream& operator>>(istream& is, Rectangle& r);
istream& operator>>(istream& is, UpTriangle& t);
istream& operator>>(istream& is, DownTriangle& d);
istream& operator>>(istream& is, Diamond& dm);
#endif
