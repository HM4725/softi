#include <stdio.h>

// stack은 주소 번지값이 작아지는 방향으로 증가
// 원래 c표준은 parameter는 오른쪽에서 왼쪽으로 push됨.
// 하지만 64-bit linux, gcc에선 오른쪽에서 왼쪽으로
// parameter를 여러 레지스터에 저장하고, 그 다음 
// 반대 방향으로 스택에 저장함.

// 정리는 addr_32.c 주석 참조

void function(long arg0, long arg1, long arg2) {
	char* p = (char *)&arg0 + 7;
	int i;

	printf("&arg0: %p \\ arg0: %016lx\n", &arg0, arg0);
	printf("&arg1: %p \\ arg1: %016lx\n", &arg1, arg1);
	printf("&arg2: %p \\ arg2: %016lx\n", &arg2, arg2);

	puts("[rbp]");
	for(i = 0; i < 3 * sizeof(long); i++) {
		if(i % 8 == 0) printf("------------------\n");
		printf("%p: %02hhx \n", p, *p);
		p--;
	}
	printf("------------------\n");
	puts("[rsp]");

	return;
}

int main() {
	function(0x1010101010101111, 0xffff, 0x123456789abcdef);

	return 0;
}
