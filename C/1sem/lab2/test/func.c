#include "func.h"
#include <stdio.h>

int func(){
    int a;
    int b;
    scanf("%d %d", &a, &b);
    return FORMULA(a, b);
}
