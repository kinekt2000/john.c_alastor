#include <stdio.h>

int main(){
        long long int inp;
        scanf("%lld",&inp);
        int count;
        for(count = 0; inp; count++)
                inp /= 10;
        printf("%d\n", count);
        return 0;
}


