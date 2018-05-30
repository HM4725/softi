#include "1_fibonacci.h"

long fibonacci(int n){

	if(n>2)
		return fibonacci(n-1)+fibonacci(n-2);
	else return 1;
}
