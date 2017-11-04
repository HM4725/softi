#include<iostream>
#include<list>
using namespace std;

template <typename T>
void print_list(list<T>& lst){
	cout<<"[ ";
	for(/*typename*/ list<T>::iterator itr=lst.begin();itr!=lst.end() ;itr++)
// 왜 앞에 typename을 써줘야함??
		cout<<*itr<<" ";

	cout<<" ]"<<endl;
}

int main(){
	list<int> lst;

	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	lst.push_back(40);

	cout<<"처음 리스트의 상태"<<endl;
	print_list(lst);

	for (list<int>::iterator itr = lst.begin(); itr != lst.end(); itr++) {

		// 만일 현재 원소가 20 이라면

		// 그 앞에 50 을 집어넣는다.

		if (*itr == 20) {

			lst.insert(itr, 50);

		}

	}

	cout << "값이 20 인 원소 앞에 50을 추가 " << endl;

	print_list(lst);

	for(list<int>::iterator itr=lst.begin() ;itr!=lst.end() ;itr++){
		if(*itr==30){
			lst.erase(itr);
			break;
		}
	}

	cout<<"값이 30인 원소를 제거한다" <<endl;
	print_list(lst);

	return 0;
}
