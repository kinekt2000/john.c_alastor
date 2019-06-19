#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP "Dragon flew away!"


void readString(char** sentence);

int main(){
    char* string;
    readString(&string);
    printf("%s\n", string);
    return 0;
}

void readString(char** sentence){
    char c;
    int size = 1;
    *sentence = calloc(size, sizeof(char));
    int i;
    int identifier = 0;
    for(i = 0;; i++){
        if (i % 5 == 0){
            size += 5;
            *sentence = realloc(*sentence, size*sizeof(char));
        }
        c = fgetc(stdin);
        if ((c == ' ' || c == '\t' ) && identifier == 0){ i--; continue;}
        else if ((c != ' ' && c != 't') && identifier == 0) identifier = 1;
        if(c == '\n') c = ' ';
        (*sentence)[i] = c;
        (*sentence)[i+1] = 0;
        if (strcmp(*sentence, STOP) == 0) break; 
        if (c == '.' || c == '?' || c == ';') break;
    }
}
