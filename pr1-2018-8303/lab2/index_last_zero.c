#include "index_last_zero.h"

int index_last_zero(int *arr, int size){
	int index;
	for (index = size-1; arr[index] != 0; index--);
	return index;
}
