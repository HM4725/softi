#include<stdio.h>

#define HM 4
#define CUBE(X) X*X*X

void main(){
	int num=HM*HM;
	puts("#define HM 4");
	printf("HM*HM=%d\n",num);

	printf("CUBE(HM)=%d\n",CUBE(HM));

}
