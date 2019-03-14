#include <stdio.h>
#define N 5

int universalMax(void* array, int length, int size, int (*cmp)(const void* a, const void* b));

int intCmp(const void* a, const void* b);
int  charCmp(const void* a, const void* b);
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
			for (int i = 0; i < N; i++)
				scanf("%c", &(cArr[i]));
			index = universalMax();
	}
}


int universalMax(void* array, int length, int size, int (*cmp)(const void* a, const void* b)){
	void* max = array;
	for (int = 0; i < length; i ++){
		if (cmp(max, array+i*size) > 0)
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
	if (*((char*)a) > *((char*)b)) return -1;
	if (*((char*)a) < *((char*)b)) return 1;
	return 0;
}

int doubleCmp(const void* a, const void* b){

}
