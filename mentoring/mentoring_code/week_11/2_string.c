#include<stdio.h>

void main(){
	char str1[6]="Good";	// [G][o][o][d][\0][?]
	char str2[]="morning";	// [m][o][r][n][i][n][g][\0]

	printf("string(str1)=%s\n",str1);		//	%s <<< address of char[]
	printf("string(str2)=%s\n",str2);

	printf("sizeof(str1)=%lu\n",sizeof str1);	// %else <<< value
	printf("sizeof(str2)=%lu\n",sizeof(str2));

	str1[5]=65;	//'A'==65
	str2[1]=97;	//'a'==97
	printf("string(str1)=%s\n",str1);
	printf("string(str2)=%s\n",str2);

	/////////////////////////////////
	puts("/////////////////////////////");

	char str3[]="abc";
	char str4[]={'a','b','c'};
	char str5[]={'a','b','c',0};
	char str6[5]={'a','b','c'};		// [a][b][c][0][0]
	printf("string(str3)=%s\n",str3);	// %s: 0값까지 읽음
	printf("string(str4)=%s\n",str4);	// Warning: abcme, abc [print]
	printf("string(str5)=%s\n",str5);
	printf("string(str6)=%s\n",str6);

	for(int i=0; i<sizeof(str6)/sizeof(char) ; i++){
		printf("str6[%d]=%d\n",i,str6[i]);
	}
}

