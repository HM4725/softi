#include<stdio.h>

int main(){
	FILE* fp_read= fopen("/home/leehyeonmin/Desktop/source.txt","r");
	FILE* fp_write= fopen("/home/leehyeonmin/Desktop/destination.txt","w");
	if (fp_read==NULL||fp_write==NULL){
		puts("error!");
		return -1;
	}

//int fscanf(FILE* stream, const char* format, ...);
	int data;
	while(fscanf(fp_read,"%d",&data)>0){
// int fprintf(FILE* stream, const char* format, ...);
		fprintf(fp_write,"%d\n",data);
	}
	fclose(fp_read);
	fclose(fp_write);
	return 0;
}

/* We learned
   fscanf,fprintf
*/
