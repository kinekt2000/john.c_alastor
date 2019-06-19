#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char inpC;
    int id;
    int f;
    for(;;){
        id = scanf("%d", &f);
        if (id == 0 || f > 9){
            do
                inpC = fgetc(stdin);
            while (inpC != '\n');
            continue;
        }    
        printf(">>> %d\n", f);
    }
    return 0;
}
