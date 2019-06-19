#include "index_first_zero.h"

int index_first_zero(int *arr){
	int index = 0;
	for (index = 0; arr[index] != 0; index++);
	return index;
}
