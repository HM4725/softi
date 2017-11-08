#include"draw_shape.h"

Canvas::Canvas(size_t row, size_t col){
	row_=row;
	col_=col;	//size of Canvas
	Draw(cout);
}

Canvas::~Canvas(){
	row_=0;
	col_=0;
	shapes_.clear();
}

int Canvas::AddShape(const Shape &s){

	/* Prevent errors */

	if(s.width%2==0||s.height%2==0){
		cout<<"error invalid input"<<endl;
		return ERROR_INVALID_INPUT;
	}
	if(s.type==RECTANGLE){
		if(s.x-s.width/2<0||s.x+s.width/2>=(signed)row_){
			cout<<"error out of canvas"<<endl;
			return ERROR_OUT_OF_CANVAS;
		}
		else if(s.y-s.height/2<0||s.y+s.height/2>=(signed)col_){
			cout<<"error out of canvas"<<endl;
			return ERROR_OUT_OF_CANVAS;
		}
	}
	else if(s.type==TRIANGLE_UP){
		if(s.x-s.width/2<0||s.x+s.width/2>=(signed)row_){
			cout<<"error out of canvas"<<endl;
			return ERROR_OUT_OF_CANVAS;
		}
		else if(s.y<0||s.y+s.height-1>=(signed)col_){
			cout<<"error out of canvas"<<endl;
			return ERROR_OUT_OF_CANVAS;
		}
	}
	else if(s.type==TRIANGLE_DOWN){
		if(s.x-s.width/2<0||s.x+s.width/2>=(signed)row_){
			cout<<"error out of canvas"<<endl;
			return ERROR_OUT_OF_CANVAS;
		}
		else if(s.y-s.height+1<0||s.y>=(signed)col_){
			cout<<"error out of canvas"<<endl;
			return ERROR_OUT_OF_CANVAS;
		}
	}
	
	/* addshape */

	shapes_.push_back(s);
	
	return shapes_.size()-1;	// The index of the shape
}
void Canvas::DeleteShape(int index){
	if(index>=0&&index<(signed)shapes_.size()){
		vector<Shape>::iterator itr(shapes_.begin());
		itr+=index;
		shapes_.erase(itr);
	}
}
void Canvas::Draw(ostream& os){
	/* Make a paper (clear canvas) */

	vector<string> canvas;
	string canvas_row("");
	for(size_t i=0; i!=col_; ++i){
		for(size_t j=0; j!=row_; ++j){
			canvas_row+=".";
		}
		canvas.push_back(canvas_row);
		canvas_row.clear();
	}


	/* Input shapes */

	for(int i=0; i!=(signed)shapes_.size() ; ++i){
		if(shapes_[i].type==RECTANGLE){
			for(int cy=shapes_[i].y-shapes_[i].height/2;cy<=shapes_[i].y+shapes_[i].height/2;++cy){
				for(int cx=shapes_[i].x-shapes_[i].width/2;cx<=shapes_[i].x+shapes_[i].width/2;++cx){
					canvas[cy][cx]=shapes_[i].brush;
				}
			}

		}
		else if(shapes_[i].type==TRIANGLE_UP){
			for(int j=0;j<shapes_[i].height;++j){
				for(int cx=shapes_[i].x-j;cx<=shapes_[i].x+j;cx++){
					canvas[shapes_[i].y+j][cx]=shapes_[i].brush;
				}
			}
		}
		else if(shapes_[i].type==TRIANGLE_DOWN){
			for(int j=0;j<shapes_[i].height;++j){
				for(int cx=shapes_[i].x-j;cx<=shapes_[i].x+j;cx++){
					canvas[shapes_[i].y-j][cx]=shapes_[i].brush;
				}
			}
		}

	}


	/* Draw the canvas */

	os<<" ";
	for(size_t i=0;i!=row_;++i){
		os<<i%10;
	}
	os<<endl;
	for(size_t i=0;i!=col_;++i){
		os<<i%10<<canvas[i]<<endl;
	}
}
void Canvas::Dump(ostream& os){
	for(size_t i=0;i!=shapes_.size();++i){
		if(shapes_[i].type==RECTANGLE){
			os<<i<<" rect "<<shapes_[i].x<<" "
			<<shapes_[i].y<<" "<<shapes_[i].width
			<<" "<<shapes_[i].height<<" "
			<<shapes_[i].brush<<endl;
		}
		else if(shapes_[i].type==TRIANGLE_UP){
			os<<i<<" tri_up "<<shapes_[i].x<<" "
			<<shapes_[i].y<<" "<<shapes_[i].height<<" "
			<<shapes_[i].brush<<endl;
		}
		else if(shapes_[i].type==TRIANGLE_DOWN){
			os<<i<<" tri_down "<<shapes_[i].x<<" "
			<<shapes_[i].y<<" "<<shapes_[i].height<<" "
			<<shapes_[i].brush<<endl;
		}
	}
}
