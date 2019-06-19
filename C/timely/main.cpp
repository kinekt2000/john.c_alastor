#include <stdio.h>
#include <string.h>

int count(char *str){
    char *words[50];
    char* lex = strtok(str, " ");
    int count;
    for (count = 0; lex; count++){
        strcpy(words[count], lex);
        lex = strtok(NULL, " ");
    }
    count++;
    int max = 0;
    for(int i = 0; i < count; i++){
        int len = 0;
        for (int j = 0; j < count; j++)
            if (strcmp(words[i], words[j]) == 0) len++;
        if (len > max) max = len;
    }
    return max;
}


int main(){
    char str[200];
    strcpy(str, "mw  wue minpvrxnos aivedg mqfpv  pbhlzfpi zj  l ri yopzw tnxy  sy u rgrklr   y  hkxs mpbjyk mswm y dheydp m  r zeicyqgyif");
    printf("%d\n", count(str));
    return 0;
}
