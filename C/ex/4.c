#include <stdio.h>

int main(){
    unsigned long i;
    int bits, p;
    scanf("%lld", &i);
    printf("%lld\n", i);
    for (bits = 0, p = 0; i; bits++){
        if (i & 1) p++;
        i >>= 1;
    }

    if (bits == p) printf("%d\n", p);
    else printf("False\n");
    return 0;
}
