#include<iostream>
using namespace std;

void magic_square(int,int**);

int main(){
	int array_size;
	cin >>array_size;

	if(array_size<3||array_size%2==0)
		return 0;

/* 메모리할당 */
	int ** array = new int *[array_size];
	for(int i=0; i<array_size; i++){
		array[i]=new int[array_size]();
	}
/* 마방진 생성 */
	magic_square(array_size,array);

/* 2차원배열 출력 */
	for(int m=0 ; m<array_size ; m++){
		for(int n=0;n<array_size;n++){
			cout<<array[m][n]<<" ";
		}
		cout<<endl;
	}

/* 메모리 해제 */
	for( int i=0; i<array_size; i++) {
		delete [] array[i];
	}
	delete [] array;
	
	return 0;
}

void magic_square(int N,int ** array){
	int m=0, n=(N-1)/2;
	for(int i=1; i<=N*N; i++){
		array[m][n]=i;
		m=m-1;
		n=n+1;
		if(m==-1&&n!=N)
			m=N-1;
		if(m!=-1&&n==N)
			n=0;
		if((m==-1&&n==N)||array[m][n]!=0){
			m=m+2;
			n=n-1;
		}
	}
}
