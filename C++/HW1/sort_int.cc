#include<iostream>

using namespace std;

void sort_int(int,int*);
void swap(int*,int*);

int main(){
	int num;
	cin >>num;
	if( num<1)
		return 0;

/* 메모리할당 */
	int * array= new int[num]();

/* 정수들 입력 */
	for(int i=0; i<num;i++)
		cin >> array[i];
/* 정수 정렬 */
	sort_int(num,array);

/* 배열 출력 */
	for(int i=0; i<num; i++)
		cout << array[i] <<" ";
	cout<<endl;	

/* 메모리 해제 */
	delete[] array;

	return 0;
}
	
void sort_int(int N, int * array){
	int k=0;
	while(k<N-1){
		for(int i=0;i<N-1 ; i++){
			if(array[i]>array[i+1])
				swap(array+i,array+i+1);
		}
		k=k+1;
	}
}

void swap(int*A,int*B){
	int hold;

	hold=*A;
	*A=*B;
	*B=hold;
}	
