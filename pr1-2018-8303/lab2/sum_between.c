#include <stdlib.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_between(int *arr, int size){
	int first = index_first_zero(arr);
	int last = index_last_zero(arr,size);
	int sum = 0;
	int i;
	for (i = first+1; i < last; i++)
		sum += abs(arr[i]);
	return sum;
}
