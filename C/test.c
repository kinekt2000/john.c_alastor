#include <stdio.h>
#include <stdlib.h>
#define N 5


void swap(int* x, int* y){
    if(*x != *y){
        *x ^= *y;
        *y ^= *x;
        *x ^= *y;
    }
}

int main(){
    int x = 16;
    int y = 23;

    swap(&x, &y);

    printf("%d %d\n", x, y);
}
