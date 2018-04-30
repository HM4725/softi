#ifndef __point2d_h__
#define __point2d_h__

using namespace std;

struct Point{
	int x_,y_;
	char name;

	Point();
	Point(const Point& p);
	explicit Point(int c);
	Point(int x, int y);

	Point operator -();
};

Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
Point operator*(const Point& lhs, const Point& rhs);



#endif
