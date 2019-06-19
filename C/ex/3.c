#include <stdio.h>
#include <ctype.h>

#define SZ 200

int main(){
    int i, j;
    char inp[SZ+2];
    char out[SZ+2];
    fgets(inp, SZ+2, stdin);
    for(i = 0, j = 0; inp[i]; i++){
        if (islower(inp[i])) continue;
        out[j] = inp[i];
        j++;
    }
    out[j] = 0;
    printf("%s", out);
    return 0;
}
