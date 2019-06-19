#include <stdio.h>
#include <stdlib.h>

struct Symbol{
    char c;
    int code;
};

int main(){
    struct Symbol* alpha = (struct Symbol*) malloc(1*sizeof(struct Symbol));
    struct Symbol* buffer; 
    int ident = scanf("{'%c',%d}", &(alpha[0].c), &(alpha[0].code));
    int max = alpha[0].code;
    int i;
    for (i = 1; ident; i++){
        buffer = (struct Symbol*) realloc(alpha, (i+1)*sizeof(struct Symbol));
        if (buffer == NULL) return -1;
        alpha = buffer;

        ident = scanf("{'%c',%d}", &(alpha[i].c), &(alpha[i].code));
        if (alpha[i].code > max && ident) max = alpha[i].code;
    }

    int j;
    for (j = 0; j < i; j++){
        if (alpha[j].code == max) printf("%c\n", alpha[j].c);
    }
    return 0;
}
