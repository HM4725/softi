#include<stdio.h>

void show_array(const double ar[], int n);
void mult_array(double arr[], int n, double mult);

int main(){
	double rates[5] = {88.99, 100.12};
	const double locked[4] = {0.08, 0.075, 0.725, 0.12};
	const double *pc=rates;

//	*pc=29.89; // 간접 변경 불가
//	pc[2]=241; // 간접 변경 불가
	pc++;
	pc=locked;
	pc=&rates[3];
	show_array(rates,5);
	show_array(locked,4);
	mult_array(rates,5,1.2);
//	mult_array(locked,4,1.2);	
		/* arr=locked
			arr: 그냥 double*
			locked: const double locked
			arr을 통해 locked의 elements들을 간접 변경 가능
			그러면 const 의 의미가 없어짐
			>>> nonconst변수에 const값을 넣을 수 없음 (주소 값)
			>>> 주소가 아닌 일반적인 값은 상관없음
								*/

	return 0;
}


void show_array(const double ar[], int n){ }
void mult_array(double arr[], int n, double mult){ }
