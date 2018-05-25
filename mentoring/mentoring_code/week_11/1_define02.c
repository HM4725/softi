#include<stdio.h>

#define HM 2+2
#define CUBE(X) X*X*X

void main(){
	int num=HM*HM;
	puts("#define HM 2+2");
	printf("HM*HM=%d\n",num);
		// num >>> HM*HM >>> 2+2*2+2=8

	printf("CUBE(HM)=%d\n",CUBE(HM));
		// CUBE(HM)>>>CUBE(2+2)>>>2+2*2+2*2+2
}
