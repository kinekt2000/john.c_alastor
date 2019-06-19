#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP "Dragon flew away!"

void readString(char** sentence);
int readText(char*** text);
int processing(char*** text, int count);
void processSentence(char** sentence);


int main(){
    char** text;
    int count = readText(&text);
    //for(int i = 0; i < count; i++){
    //    printf("%s\n", (text)[i]);
    //}
    int new_count = processing(&text, count);
    for(int i = 0; i < new_count; i++){
        printf("%s\n", (text)[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d\n", count-1, new_count-1);
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
        if ((c == ' ' || c == '\t' ) && identifier == 0) { i--; continue;}
        else if ((c != ' ' && c != 't') && identifier == 0) identifier = 1;
        if(c == '\n') c = ' ';
        (*sentence)[i] = c;
        (*sentence)[i+1] = 0;
        if (strcmp(*sentence, STOP) == 0) break; 
        if (c == '.' || c == '?' || c == ';') break;
    }
}

// Jailed :c
int readText(char*** text){
    *text = malloc(sizeof(char));
    char* sentence;
    int size = 0;
    do{
        size++;
        *text = realloc(*text, size*sizeof(char*));
        readString(&sentence);
        (*text)[size-1] = sentence;
    }while (strcmp(sentence, STOP));
    return size;
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

// Jailed :c
int processing(char*** text, int count){
    int new_count = 0;
    char** new_text = malloc(sizeof(char*));
    for(int i = 0; i < count; i++){
        processSentence(&(*text)[i]);
        if (*((*text)[i])){
            new_text = realloc(new_text, (new_count+1)*sizeof(char));
            new_text[new_count] = malloc((strlen((*text)[i])+1)*sizeof(char));
            strcpy(new_text[new_count], (*text)[i]);
            free((*text)[i]);
            new_count++;
        }
    }
    free(*text);
    *text = new_text;
    return new_count;
}

