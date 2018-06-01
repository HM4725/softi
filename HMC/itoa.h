#ifndef CIPHER

#define CIPHER 100
char* itoa(char[],int);

char* itoa(char Decimal[],int num){
	//DecimalSize==CIPHER
	char temp;
	int remain,i;
	for(i=0; num!=0 && i<CIPHER ; i++){
		remain=num%10;
		num/=10;
		Decimal[i]='0'+remain;
	}
	Decimal[i]='\0';
	int begin=0, end=i-1;
	while(begin<end){
		temp=Decimal[begin];
		Decimal[begin]=Decimal[end];
		Decimal[end]=temp;

		begin++;
		end--;
	}

	return Decimal;
}
#endif
