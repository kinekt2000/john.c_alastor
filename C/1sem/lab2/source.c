#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int *arr){
	int index = 0;
	for (index = 0; arr[index] != 0; index++);
	return index;
}

int index_last_zero(int *arr, int size){
	int index;
	for (index = size-1; arr[index] != 0; index--);
	return index;
}

int sum_between(int *arr, int size){
	int first = index_first_zero(arr);
	int last = index_last_zero(arr,size);
	int sum = 0;
	int i;
	for (i = first+1; i < last; i++)
		sum += abs(arr[i]);
	return sum;
}
	
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

int main()
{
	char finish;
	int nums[100];
	int ind = 0;
	short int op;
	scanf("%hd", &op);
	while (finish != '\n'){
		scanf("%d%c", &nums[ind], &finish);
		ind++;
		}
	switch (op){
	case 0:
		printf("%d\n", index_first_zero(nums));
		break;
	case 1:
		printf("%d\n", index_last_zero(nums, ind));
		break;
	case 2:
		printf("%d\n", sum_between(nums, ind));
		break;
	case 3:
		printf("%d\n", sum_before_and_after(nums, ind));
		break;
	default:
		printf("Данные некорректны\n");
		break;
	}
	return 0;
}
