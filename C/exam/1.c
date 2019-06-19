#include <stdio.h>



int main(){
    int edge;
    int h, m;
    int time;
    int i;
    scanf("%d\n", &edge);
    do{
        i = scanf("{%d:%d}", &h, &m);
        time = ()h * 60 + m;
        if (i && time > edge){
            printf("{%d:%d}", h, m);
        }
    }
    while (i);
    return 0;
}
