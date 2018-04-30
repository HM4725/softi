#include<stdio.h>
int main() {
// FILE* fopen(const char* filename, const char* mode);
// r : read only, r+ : read and write (beginning of the file)
// w : truncate and write, w+ : read and write (beginning of the file)
// a : write (always end of file), a+ : read and write (always end)
// b : binary, ignored.
	FILE* fp_read = fopen("/home/leehyeonmin/Desktop/source.txt", "r");
	FILE* fp_write = fopen("/home/leehyeonmin/Desktop/destination.txt","w");
	if (fp_read == NULL||fp_write == NULL){
		puts("error!");
		return -1;
	}// Error in opening the file.
// size_t fread(void* ptr, size_t size, size_t nitems, FILE* stream);
	char buf[1024];
	size_t read =0;
	while((read=fread(buf,1,1024,fp_read))>0){
// size_t fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream);
		size_t written=fwrite(buf,read,1,fp_write);
	}

	fclose(fp_read);
	fclose(fp_write);

	return 0;
}

/* We learned
   open, close
   read, write
*/
