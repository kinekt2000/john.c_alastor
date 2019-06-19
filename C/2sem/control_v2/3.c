#include <stdio.h>
#include <math.h>

#define LEN 5

int count_if(void* base, size_t num, size_t size, int (*pred)(const void*));
int predInt(const void*);
int predDou(const void*);

int main(){
	int arrInt[LEN];
	double arrDou[LEN];
	int type;
	int count;

	scanf("%d", &type);
	if (type == 4){
		for (size_t i = 0; i < LEN; i ++)
			scanf("%d", &(arrInt[i]));
		count = count_if(arrInt, LEN, sizeof(int), predInt);
	}
	else if (type == 8){
		for (size_t i = 0; i < LEN; i++)
			scanf("%lf", &(arrDou[i]));
		count = count_if(arrInt, LEN, sizeof(double), predDou);
	}
	else count = 0;

	printf("%d\n", count);
	return 0;
}


int count_if(void* base, size_t num, size_t size, int(*pred)(const void*)){
	int count = 0;
	for (size_t i = 0; i < num; i ++)
		if (pred(base + i*size)) count ++;
	return count;
}

int predInt(const void* a){
	return (*((int*)a) % 2 != 0 & *((int*)a) % 3 == 0);
}

int predDou(const void* a){
	double trash;
	if (modf(*((double*)a), &trash) > 0.000000001) return 0;
	int ia = (int)*((double*)a);
	return ((ia % 2 != 0) && (ia % 3 == 0));
}
