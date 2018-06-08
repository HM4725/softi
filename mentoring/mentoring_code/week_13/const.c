//@ 이현민
//@ const 
//@ pointer
//@ double pointer
//@ array
//@ 2018.06.06
//@ initialization part, operation part 

/*
   [const] 자료형 [const] 포인터 [const] 변수명
*/
#include<stdio.h>

int main(){
	int n1=3,n2=5;
	const int cn=10; // int const와 같음

	n1=7;
//	cn=7;	// error: assignment of read-only variable 'cn'

	//############################

	int arr[3]={1,2,3};		// int* const arr 과 비슷
	const int carr[4]={5,4};// const int* const arr 과 비슷

	arr[0]=7;
//	carr[0]=7;	// error: assignment of read-only location 'carr[0]';

	//#############################

	int* pn=&n1;
	const int* pcn=&n1;	// &n2, cn 가능
	int* const cpn=&n1; // &n2, arr 가능
	const int* const cpcn=&cn;	// &n2, &cn, arr, carr가능

	*pn=1010;
	pn=&n2;
	*pn=1010;
//	pn=&cn;		// nonconst pointer = address of const variable (X)
	*pn=1010;

	*pn=1010;
	pcn=&n2;
//	*pcn=1010;	// 간접 변경 불가
	pcn=&cn;
//	*pcn=1010;	// 간접 변경 불가

	*cpn=1010;
//	cpn=&n2;	// 다른 변수를 가리킬 수 없음
	*cpn=1010;
//	cpn=&cn;	// 다른 변수를 가리킬 수 없음
	*cpn=1010;
	//#############################

	int** ppn=&pn;
	const int** ppcn=&pcn;	//const int* 변수의 주소값만 들어갈 수 있음.
	// (const int)** ppcn	// const int형에 대한 이중 포인터
	int *const* pcpn=&cpn;	//int* const 변수와 int* 변수의 주소값이 들어갈 수 있음.
	// (int* const)* pcpn	// int* 형이 값는 주소값을 상수화함
	int ** const cppn=&pn;	//int* 변수의 주소값만 들어갈 수 있음.
	// (int **)const cppn	// int** 형이 갖는 주소값을 상수화함

	ppcn++;
	(*ppcn)++;
//	(**ppcn)++;	// error: increment of read-only loation '**ppcn'

	pcpn++;
//	(*pcpn)++;	// error: increment of read-only location '*pcpn'
	(**pcpn)++;

//	cppn++;		// error: increment of read-only variable 'cppn;
	(*cppn)++;
	(**cppn)++;

	return 0;
}
