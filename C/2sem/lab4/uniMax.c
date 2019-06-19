#include <stdio.h>
#include <stdlib.h>
#define N 5

int universalMax(void* array, int length, int size, int (*cmp)(const void* a, const void* b));

int intCmp(const void* a, const void* b);
int charCmp(const void* a, const void* b);
int doubleCmp(const void* a, const void* b);


int main(){
	int size;
	int index;
	scanf("%d", &size);
	char cArr[N];
	int iArr[N];
	double dArr[N];
	switch (size){
		case 1:
			for (int i = 0; i < N; i++){
				scanf("%c", &(cArr[i]));
				//printf("%s\n", cArr);
				if (cArr[i] == ' ') i--;
			}
			index = universalMax(cArr, N, size, charCmp);
			break;
		case 4:
			for (int i = 0; i < N; i++)
				scanf("%d", &(iArr[i]));
			index = universalMax(iArr, N, size, intCmp);
			break;
		case 8:
			for (int i = 0; i < N; i++)
				scanf("%lf", &(dArr[i]));
			index = universalMax(dArr, N, size, doubleCmp);
			break;
		default :
			printf("Wrong size\n");
			return 1;
	}
	printf("%d\n", index);
	return 0;
}


int universalMax(void* array, int length, int size, int (*cmp)(const void* a, const void* b)){
	void* max = array;
	for (int i = 0; i < length; i ++){
		if (cmp(array + i*size, max) > 0)
			max = array+i*size;
	}
	return (max - array)/size;
}

int intCmp(const void* a, const void* b){
	if (*((int*)a) > *((int*)b)) return 1;
	if (*((int*)a) < *((int*)b)) return -1;
	return 0;
}

int charCmp(const void* a, const void* b){
	/*if (*((char*)a) > *((char*)b)) return -1;
	if (*((char*)a) < *((char*)b)) return 1;
	return 0;*/
	return *((char*)a) - *((char*)b);
}

int doubleCmp(const void* a, const void* b){
	if (abs(*((double*)a) - *((double*)b)) < 0.0001) return 0;
	if (*((double*)a) < *((double*)b)) return -1;
	return 1;
}
