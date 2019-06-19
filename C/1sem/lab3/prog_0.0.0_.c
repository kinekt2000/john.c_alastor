#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP "Dragon flew away!"


int readText(char*** text);
char* readString();

int main(){
    char** text = malloc(10*sizeof(char*));
    int count = readText(&text);
    for(int i = 0; i < count; i++){
        printf("%s\n", (text)[i]);
    }
    return 0;
}

char* readString(){
    char c;
    int size = 1;
    char* out = calloc(size, sizeof(char));
    int i;
    for(i = 0;; i++){
        if (i % 5 == 0){
            size += 5;
            out = realloc(out, size*sizeof(char));
        }
        c = fgetc(stdin);
        if(c == '\n') c = ' ';
        out[i] = c;
        if (c == '.' || c == '?' || c == ';' || c == '!') break;
    }
    out[i+1] = 0;
    for(int j = 0; out[j] == ' ' || out[j] == '\t'; i++) out = &out[j+1];
    if (out[strlen(out)-1] == '!' && strcmp(out, STOP)) *out = 0;
    return out;
}

int readText(char*** text){
    char* sentence;
    int size = 0;
    do{
        size++;
        *text = realloc(*text, size*sizeof(char*));
        sentence = readString();
        (*text)[size-1] = sentence;
    }while (strcmp(sentence, STOP));
    return size;
}
