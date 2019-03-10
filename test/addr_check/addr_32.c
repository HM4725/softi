#include <stdio.h>

// stack은 주소 번지값이 작아지는 방향으로 증가
// 원래 c표준은 parameter는 오른쪽에서 왼쪽으로 push됨.
// 하지만 64-bit linux, gcc에선 오른쪽에서 왼쪽으로
// parameter를 여러 레지스터에 저장하고, 그 다음 
// 반대 방향으로 스택에 저장함.

/*	[인자 전달 방법 정리]
 *	1. 32-bit환경: 대부분 스택으로 전달
 *	2. 64-bit환경: 대부분 레지스터로 전달
 *			64-bit calling convention 참조
 *	3. 인자 전달 방향: 오른쪽에서 왼쪽으로
 */

void function(int arg0, int arg1, int arg2) {
	char* p = (char *)&arg0 + 3;
	int i;

	printf("&arg0: %p \\ arg0: %08x\n", &arg0, arg0);
	printf("&arg1: %p \\ arg1: %08x\n", &arg1, arg1);
	printf("&arg2: %p \\ arg2: %08x\n", &arg2, arg2);

	puts("[ebp]");
	for(i = 0; i < 3 * sizeof(int); i++) {
		if(i % 4 == 0) printf("------------------\n");
		printf("%p: %02hhx \n", p, *p);
		p--;
	}
	printf("------------------\n");
	puts("[esp]");

	return;
}

int main() {
	function(0x10, 0xffff, 0x12345678);

	return 0;
}
