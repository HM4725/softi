#include<stdio.h>
#include<termio.h>

#ifndef HMC
#define HMC
int getch(void){
	int ch;

	struct termios buf;
	struct termios save;

	tcgetattr(0,&save);
	buf=save;

	buf.c_lflag &= ~(ICANON|ECHO);
	buf.c_cc[VMIN]=1;
	buf.c_cc[VTIME]=0;

	tcsetattr(0,TCSAFLUSH,&buf);

	ch=getchar();
	
	tcsetattr(0,TCSAFLUSH,&save);

	return ch;
}
#endif

/*	1.To use getch() ---> conio.h (MS DOS header file)
	2.already include <stdio.h>
	3.How to use : #include "getch.h" -->	getch()		*/
