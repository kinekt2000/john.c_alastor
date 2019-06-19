#include <stdio.h>

int main(){
    int a;
    int bits;
    scanf("%d", &a);
    int tmp = a;
    for (bits = 0; tmp; bits++) tmp >>= 1;
    for (; bits; bits--){

        if (a & (1 << bits-1)) printf("1");
        else printf("0");
    }
    return 0;
}
