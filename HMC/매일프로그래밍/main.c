/*
 *	Daily Programming 01
 *	Source Code
 *	Made by HMC
 *	
 *	Safe Version
 *
 */


#include<stdio.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

#define STATUS_SUCCESS 0
#define STATUS_FAIL -1

#define ctoi(x) (x-'0')

#define WINDOWS
//#define LINUX

char isWrongRange(int num);
char isWrongAddress(char* address);
int addressToInt(char* address, int itr, int size);

int main() {
	int first, second, third, fourth, temp;
	unsigned char IP[4] = { 0 };
	char addressStr[20];
	int lengthOfAddress;
	int tempLength;
	int firstCase = TRUE;

	printf("Input: ");

#ifdef WINDOWS
	scanf_s("%s", addressStr, sizeof(addressStr));
#endif

#ifdef LINUX
		scanf("%s", addressStr);
#endif
	lengthOfAddress = strlen(addressStr);

	if (isWrongAddress(addressStr)) {
		printf("ERROR: wrong input!\n");
#ifdef WINDOWS
		system("pause");
#endif
		return STATUS_FAIL;
	}

	printf("Output: [");

	for (first=1; first <= 3; first++) {
		for (second=1; second<= 3; second++) {
			for (third=1; third <= 3; third++) {
				for (fourth=1; fourth<= 3; fourth++) {

					tempLength = first + second + third + fourth;
					if (tempLength == lengthOfAddress) {

						temp = addressToInt(addressStr, 0, first);
						if (temp == STATUS_FAIL) continue;
						if (isWrongRange(temp))	continue;
						IP[0] = temp;

						temp = addressToInt(addressStr, first, second);
						if (temp == STATUS_FAIL) continue;
						if (isWrongRange(temp))	continue;
						IP[1] = temp;

						temp = addressToInt(addressStr, first+second, third);
						if (temp == STATUS_FAIL) continue;
						if (isWrongRange(temp))	continue;
						IP[2] = temp;

						temp = addressToInt(addressStr, first+second+third, fourth);
						if (temp == STATUS_FAIL) continue;
						if (isWrongRange(temp))	continue;
						IP[3] = temp;

						printf("%s\'%d.%d.%d.%d\'", firstCase ? "" : ", ", IP[0], IP[1], IP[2], IP[3]);
						firstCase = FALSE;
					}

				}
			}
		}
	}

	printf("]\n");

#ifdef WINDOWS
	system("pause");
#endif

	return STATUS_SUCCESS;
}

char isWrongRange(int num) {
	return (num < 0 || num > 255) ? TRUE : FALSE;
}

char isWrongAddress(char* address) {
	char checkChar;
	int lengthOfAddress = strlen(address);
	if (lengthOfAddress < 4 || lengthOfAddress >12) return TRUE;

	for (int i = 0; i < lengthOfAddress; i++) {
		checkChar = address[i];
		if (checkChar<'0' || checkChar>'9') {
			return TRUE;
		}
	}

	return FALSE;
}

int addressToInt(char* address, int itr, int size) {
	int result = 0;
	int firstDigit= ctoi(address[itr]);

	if (firstDigit == 0 && size > 1)	return STATUS_FAIL;

	for (int i = 0; i < size; i++) {
		result *= 10;
		result += ctoi(address[itr+i]);
	}
	return result;
}