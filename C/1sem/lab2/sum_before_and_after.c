#include <stdlib.h>
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_before_and_after(int *arr, int size){
	int first = index_first_zero(arr);
	int last = index_last_zero(arr,size);
	int sum;
	int i;
	for (i = 0; i < first; i++)
		sum += abs(arr[i]);
	for (i = last+1; i < size; i++)
		sum += abs(arr[i]);
	return sum;
}
