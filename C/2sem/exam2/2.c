#include <stdio.h>

void retint(int i){
    if (!i) return;
    printf("%d", i%10);
    retint(i/10);
}

int main() {
    int i;
    scanf("%d", &i);

    retint(i);
    return 0;
}
