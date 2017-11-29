#include "draw_shape2.h"
#define EMPTY 0

Canvas::Canvas(size_t row, size_t col){
	row_=row;
	col_=col;
	canvas_.resize(col_);
	for(vector<vector<char> >::iterator itr=canvas_.begin();itr!=canvas_.end();++itr){
/*		for(size_t i=0;i<row;++i){
			itr->push_back('.');
		}*/
		(*itr).resize(row_);
	}
	for(size_t i=0; i<col_; i++){
		for(size_t j=0; j<row_; j++){
			canvas_[i][j]='.';
		}
	}
}
Canvas::~Canvas(){
	row_=0;
	col_=0;
	canvas_.clear();
}
void Canvas::Resize(size_t w, size_t h){
	row_=w;
	col_=h;
	
	canvas_.resize(h);
	for(vector<vector<char> >::iterator itr=canvas_.begin();itr!=canvas_.end();++itr){
		itr->resize(w);
	}

	for(vector<vector<char> >::iterator itr1=canvas_.begin();itr1!=canvas_.end();++itr1){
		for(vector<char>::iterator itr2=itr1->begin();itr2!=itr1->end();++itr2){
			if(*itr2==EMPTY)	*itr2='.';	//조건연산자==,대입연산자=.
		}
	}

}
bool Canvas::Draw(int x, int y, char brush){
	if(x>=0&&x<(signed)row_&&y>=0&&y<(signed)col_){
		canvas_[y][x]=brush;
		return true;
	}
	else {
		return false;
	}
}
void Canvas::Clear(){
	for(vector<vector<char> >::iterator itr1=canvas_.begin();itr1!=canvas_.end();++itr1){
		for(vector<char>::iterator itr2=itr1->begin();itr2!=itr1->end();itr2++){
				*itr2='.';
		}
	}
}

ostream& operator<<(ostream& os, const Canvas& c){//friend >> no member of class
	os<<' ';
	for(size_t i=0;i<c.row();++i){
		os<<i%10;
	}
	os<<endl;

	int k=0;
	const vector<vector<char> > temp=c.canvas();// 왜 for문에서 temp대신 c.canvas()쓰면 오류??
/*	for(vector<vector<char> >::const_iterator itr1=temp.cbegin();itr1!=temp.cend();++itr1){
		os<<k%10;
		k++;
		for(vector<char>::const_iterator itr2=itr1->cbegin();itr2!=itr1->cend();++itr2){
			os<<(int)(*itr2) << " ";
		}
		os<<endl;
	}
/////////////////////////////////////
	for(vector<vector<char> >::const_iterator itr1=c.canvas_.cbegin();itr1!=c.canvas_.cend();++itr1){
		os<<k%10;
		k++;
		for(vector<char>::const_iterator itr2=itr1->cbegin();itr2!=itr1->cend();++itr2){
			os<<(int)(*itr2) << " ";
		}
		os<<endl;
	}
///////////////////////////////////////
*/	for(vector<vector<char> >::const_iterator itr1=c.canvas().cbegin();itr1!=c.canvas().cend();++itr1){
		os<<k%10;
		k++;
		for(vector<char>::const_iterator itr2=itr1->cbegin();itr2!=itr1->cend();++itr2){
			os<<(int)(*itr2) << " ";
		}
		os<<endl;
	}


	return os;
}

Shape::~Shape(){
	x_=0;
	y_=0;
	h_=0;
	brush_=0;
}
void Shape::InputVar(int x,int y,int h,char brush){
	x_=x;
	y_=y;
	h_=h;
	brush_=brush;
}

void Rectangle::Draw(Canvas* canvas) const{
	for(int i=y_; i<y_+h_;i++){
		for(int j=x_; j<x_+w_;j++){
			canvas->Draw(j,i,brush_);
		}
	}
}
void Rectangle::Inputw(int w){
	w_=w;
}
void UpTriangle::Draw(Canvas* canvas) const{
	for(int i=y_;i<y_+h_;i++){
		for(int j=x_-(i-y_);j<=x_+(i-y_);j++ ){
			canvas->Draw(j,i,brush_);
		}
	}
}
void DownTriangle::Draw(Canvas* canvas) const{
	for(int i=y_;i>y_-h_;i--){
		for(int j=x_-(y_-i);j<=x_+(y_-i);j++){
			canvas->Draw(j,i,brush_);
		}
	}
}
void Diamond::Draw(Canvas* canvas) const{
	for(int i=y_;i<=y_+h_;i++){
		for(int j=x_-(i-y_);j<=x_+(i-y_);j++){
			canvas->Draw(j,i,brush_);
		}
	}
	for(int i=y_+2*h_;i>y_+h_;i--){
		for(int j=x_-(y_+2*h_-i);j<=x_+(y_+2*h_-i);j++){
			canvas->Draw(j,i,brush_);
		}
	}
}

istream& operator>>(istream& is, Rectangle& r){
	int x,y,w,h;
	char brush;
	is>>x>>y>>w>>h>>brush;
	r.InputVar(x,y,h,brush);
	r.Inputw(w);
	return is;
}
istream& operator>>(istream& is, UpTriangle& t){
	int x,y,h;
	char brush;
	is>>x>>y>>h>>brush;
	t.InputVar(x,y,h,brush);
	return is;
}
istream& operator>>(istream& is, DownTriangle& d){
	int x,y,h;
	char brush;
	is>>x>>y>>h>>brush;
	d.InputVar(x,y,h,brush);
	return is;
}
istream& operator>>(istream& is, Diamond& dm){
	int x,y,h;
	char brush;
	is>>x>>y>>h>>brush;
	dm.InputVar(x,y,h,brush);
	return is;
}
