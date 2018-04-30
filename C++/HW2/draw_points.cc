#include<iostream>

using namespace std;

struct coordinate {
	int x;
	int y;
};

int main(){
	int m=-1,n=-1,k=0;
	coordinate *point=new coordinate[k+1];

	while(true){
		bool exist=false;
		cin>>point[k].x>>point[k].y;

		if(point[k].x<0||point[k].y<0)
			break;
		if(point[k].x>n)
			n=point[k].x;
		if(point[k].y>m)
			m=point[k].y;

		for(int i=0;i<=m;i++){
			for(int j=0;j<=n;j++){
				for(int h=0;h<=k;h++){
					if (i==point[h].y&&j==point[h].x)
						exist=true;
				}
			if(exist==true)
				cout<<"*";
			else cout<<".";
			exist=false;
			}
			cout<<endl;
		}
		k++;
	}
	delete [] point;
	return 0;
}
