#include <stdio.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"


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
