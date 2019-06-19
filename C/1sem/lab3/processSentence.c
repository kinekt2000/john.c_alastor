#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP "Dragon flew away!"

void readString(char** sentence);
void processSentence(char** sentence);


int main(){
    char* string;
    readString(&string);
    processSentence(&string);
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
        if ((c == ' ' || c == '\t' ) && identifier == 0) continue;
        else if ((c != ' ' && c != 't') && identifier == 0) identifier = 1;
        if(c == '\n') c = ' ';
        (*sentence)[i] = c;
        (*sentence)[i+1] = 0;
        if (strcmp(*sentence, STOP) == 0) break; 
        if (c == '.' || c == '?' || c == ';') break;
    }
}

void processSentence(char** sentence){
    char buffer[strlen(*sentence)+1];
    strcpy(buffer, *sentence);
    int identifier = 0;
    char* word = strtok(buffer, " ,.;?");
    for(int i = 0; word; i++){
        for(int j = 1; j < strlen(word)-1; j++)
            if (word[j] > 47 && word[j] < 58) identifier = 1;
        word = strtok(NULL, " ,.;?");
    }
    if (identifier) **sentence = 0;
}
