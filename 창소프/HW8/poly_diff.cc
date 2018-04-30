#include<iostream>
#include<vector>

using namespace std;

class Polynominal{
	public:
		Polynominal(vector<int>& coeffs,int max){
			for(vector<int>::iterator itr=coeffs.begin();itr!=coeffs.end();itr++){
				_coeffs.push_back(*itr);
			}
			transformation.resize(max);
			for(vector<vector<int> >::iterator itr=transformation.begin();itr!=transformation.end();itr++){
				(*itr).resize(max+1);
			}
			int k=1;
			for(vector<vector<int> >::iterator itr1=transformation.begin();itr1!=transformation.end();itr1++){
				for(vector<int>::iterator itr2=itr1->begin();itr2!=itr1->end();itr2++){
					if(itr2==(itr1->begin())+k) *itr2=k;
					else *itr2=0;
				}
				k++;
			}
		
		}
		
		void differential(){
			int temp,deg;
			for(vector<vector<int> >::iterator itr1=transformation.begin();itr1!=transformation.end();itr1++){
				temp=0;
				deg=0;
				for(vector<int>::iterator itr2=itr1->begin();itr2!=itr1->end();itr2++){
					temp+=(*itr2)*_coeffs[deg];
					deg++;
				}
				diff_coeffs.push_back(temp);
			}
		}

		size_t calculate(int num){
			size_t sum=0;
			int degree=0;
			size_t mult;
			for(vector<int>::const_iterator itr=diff_coeffs.cbegin();itr!=diff_coeffs.cend();itr++){
				mult=1;
				for(int i=0;i<degree;i++){
					mult*=num;
				}
				sum+=(*itr)*mult;
				degree++;
			}
			return sum;
		}
		
	private:
		vector<vector<int> > transformation;
		vector<int> _coeffs;
		vector<int> diff_coeffs;
};

int main(){
	string str;
	size_t pos;
	int num;
	while(true){
		vector<string> monominals;
		cin>>str;

		while(true){
			pos=str.find('+');
			monominals.push_back(str.substr(0,pos));
			str.erase(0,pos+1);
			if(pos==string::npos) break;
		}
		
		int maxdegree=0;
		int degree;
		for(vector<string>::const_iterator itr=monominals.cbegin();itr!=monominals.cend();itr++){
			pos=(*itr).find("^");
			if(pos==string::npos){
				if(maxdegree==0&&(*itr).find("x")!=string::npos)	maxdegree=1;
				continue;
			}
			degree=stoi((*itr).substr(pos+1));
			if(degree>maxdegree)	maxdegree=degree;
		}

		vector<int> coefficients;
		int coefficient=0;
		coefficients.resize(maxdegree+1);
		for(vector<string>::const_iterator itr=monominals.cbegin();itr!=monominals.cend();itr++){
			pos=(*itr).find("x");
			if(pos==string::npos) {
				coefficient=stoi(*itr);
				coefficients[0]=coefficient;
			}
			else if((*itr).find("^")==string::npos){
					if(pos==0){coefficient=1;}
					else {coefficient=stoi((*itr).substr(0,pos));}
					coefficients[1]=coefficient;
			}
			else{
				if(pos==0) {coefficient=1;}
				else {coefficient=stoi((*itr).substr(0,pos));}
				pos=(*itr).find("^");
				degree=stoi((*itr).substr(pos+1));
				coefficients[degree]=coefficient;
			}
		}

		Polynominal poly(coefficients,maxdegree);
		poly.differential();

		cin>>num;

		cout<<poly.calculate(num)<<endl;
	}
	return 0;
}
