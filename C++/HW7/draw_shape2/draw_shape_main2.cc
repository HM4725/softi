// draw_shape_main.cc
#include <string>
#include "draw_shape2.h"
int main() {
	vector<Shape*> shapes;
	size_t row, col;
	cin >> row >> col;
	Canvas canvas(row, col);
	cout << canvas;
	while (true) {
		string tok;
		cin >> tok;
		if (tok == "add") {
			string type;
			cin >> type;
			if (type == "rect") {
				Rectangle* shape = new Rectangle();	// Rectangle vs Rectangle()
				cin >> *shape;	
				shapes.push_back(shape);
			}
			else if (type == "tri_up") {
				UpTriangle* shape= new UpTriangle();
				cin >> *shape;
				shapes.push_back(shape);
			}
			else if (type == "tri_down") {
				DownTriangle* shape = new DownTriangle();
				cin >> *shape;
				shapes.push_back(shape);
			}
			else if (type == "diamond") {
				Diamond* diamond = new Diamond();
				cin >> *diamond;
				shapes.push_back(diamond);
			}
			else continue;
		} else if (tok == "draw") {
			canvas.Clear();
			for (size_t i = 0; i < shapes.size(); ++i) shapes[i]->Draw(&canvas);
			cout << canvas;
		} else if (tok == "delete") {
			int index;
			cin >> index;//index<0 : (unsigned)-1=4294967295
			if((unsigned)index < shapes.size()) shapes.erase(shapes.begin()+index);
		} else if (tok == "dump") {
			for(size_t i=0;i<shapes.size();i++) {
				if(shapes[i]->type()=="rect")
					cout << i << " rect "<< shapes[i]->x() << ' ' << shapes[i]->y() << ' ' << shapes[i]->w() << ' ' << shapes[i]->h() << ' ' << shapes[i]->brush() << endl;
				else
					cout << i <<' ' <<shapes[i]->type() << ' ' <<shapes[i]->x() << ' ' << shapes[i]->y() << ' ' << shapes[i]->h() <<' ' << shapes[i]->brush() << endl;
			}
		} else if (tok == "resize") {
			int row,col;
			cin >> row >> col;
			canvas.Resize(row,col);
		} else {
			break;
		}
	}
	for (size_t i = 0; i < shapes.size(); ++i) {
		delete shapes[i];
	}
	shapes.clear();
	return 0;
}
