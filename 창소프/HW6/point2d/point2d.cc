#include"point2d.h"
#include<iostream>

Point::Point(){
	x_=0;
	y_=0;
}
Point::Point(const Point& p){
	x_=p.x_;
	y_=p.y_;
	name=p.name;
}
/* name=p.name; 을 안써주면
   Point a(p), a=p를 할때나
   push_back(p)를 할 때
   name값이 들어가지 않음.	*/
Point::Point(int c){
	x_=c;
	y_=c;
}
Point::Point(int x, int y){
	x_=x;
	y_=y;
}
Point Point::operator -(){
	x_=-x_;
	y_=-y_;

	return *this;
}

Point operator+(const Point& lhs, const Point& rhs){
	Point point_(lhs.x_+rhs.x_,lhs.y_+rhs.y_);
	return point_;
}

Point operator-(const Point& lhs, const Point& rhs){
	Point point_(lhs.x_-rhs.x_,lhs.y_-rhs.y_);
	return point_;
}

Point operator*(const Point& lhs, const Point& rhs){
	Point point_((lhs.x_)*(rhs.x_),(lhs.y_)*(rhs.y_));
	return point_;
}

bool is_integer(const string& s){
	string::const_iterator itr = s.begin();
	for(itr=s.begin();itr!=s.end();itr++){
		if(itr==s.begin()){
				if(!(*itr=='-'||isdigit(*itr) ))	break;
		}
		else {
			if(!isdigit(*itr))	break;
		}
	}
	return !s.empty()&&(itr==s.end());
}
