#include <stdio.h>
#include <stdlib.h>

#define N 5

int multiply_two(int a);
int raise_to_three(int a);
int absolute(int a);
void forEachElement(int* array, int len, int (*func)(int a));


int main(){
	int arr[N];
	int f;
	for (int i = 0; i < N; i++)
		scanf("%d", &(arr[i]));
	scanf("%d", &f);

	switch (f){
		case 1:
			forEachElement(arr, N, multiply_two);
			break;
		case 2:
			forEachElement(arr, N, raise_to_three);
			break;
		case 3:
			forEachElement(arr, N, absolute);
			break;
		default :
			printf("Error\n");
	}
	if ( f > 0 && f < 4)
		for (int i = 0; i < N; i++)
			printf("%d\n", arr[i]);

	return 0;
}

int multiply_two(int a){
	return a*2;
}

int raise_to_three(int a){
	return a*a*a;
}

int absolute(int a){
	return abs(a);
}


void forEachElement(int* array, int len, int (*func)(int a)){
	for (int i = 0; i < len; i++)
		array[i] = func(array[i]);
}
