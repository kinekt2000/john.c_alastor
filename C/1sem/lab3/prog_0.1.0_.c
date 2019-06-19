#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP "Dragon flew away!"

void processSentence(char** sentence);
int processWord(char* word);

int main(){
    int memText = 0;
    char** text = (char**)malloc(sizeof(char*));
    char* buffer = (char*)malloc(2*sizeof(char));
    char inpC;

    int sizeText;
    for(sizeText = 0; strcmp(buffer, STOP); sizeText++){
        free(buffer);

        if (sizeText % 5 == 0){
            memText += 5;
            text = (char**)realloc(text, memText*sizeof(char*));
        }

        do
            inpC = fgetc(stdin);
        while(inpC == ' ' || inpC == '\t' || inpC == '\n');

        int memString = 10;
        text[sizeText] = (char*)malloc((memString+1)*sizeof(char));
        *(text[sizeText]) = inpC;

        int sizeString;
        for(sizeString = 1; inpC != '.' && inpC != ';' && inpC != '?'; sizeString++){
            if (sizeString % 10 == 0){
                memString += 10;
                text[sizeText] = (char*)realloc(text[sizeText], (memString+1)*sizeof(char));
            }
            inpC = fgetc(stdin);
            if (inpC == '\n') inpC = ' ';
            text[sizeText][sizeString] = inpC;
            text[sizeText][sizeString+1] = 0;
            if (strcmp(text[sizeText], STOP) == 0) break;
        }
        buffer = (char*)malloc((strlen(text[sizeText])+1)*sizeof(char));
        strcpy(buffer, text[sizeText]);
    }

    int newSizeText = 0;
    for(int i = 0; i < sizeText; i++){
        processSentence(&(text[i]));
        if (*text[i] == 0) continue;
        printf("%s\n", text[i]);
        newSizeText++;
    }

    
    printf("Количество предложений до %d и количество предложений после %d\n", sizeText-1, newSizeText-1);
    return 0;
}

int processWord(char* word){
    int identifier = 0;
    int len = strlen(word);
    int leftPointer;
    for(leftPointer = 0; word[leftPointer] >= '0' && word[leftPointer] <= '9' && leftPointer != len - 1; leftPointer++);
    int rightPointer;
    for(rightPointer = len - 1; word[rightPointer] >= '0' && word[rightPointer] <= '9' && rightPointer != 0; rightPointer--);
    //printf("%d\t%d\t%s\n", leftPointer, rightPointer, word);

    if (rightPointer - leftPointer > 1)
        for(int i = leftPointer; i <= rightPointer; i++)
            if (word[i] >= '0' && word[i] <= '9')
                identifier = 1;
    //printf("%d\n", identifier);
    if (identifier) return 1;
    else return 0;
}

 
void processSentence(char** sentence){
    char buffer[strlen(*sentence)+1];
    strcpy(buffer, *sentence);
    int identifier = 0;
    char* word = strtok(buffer, " ,.;?");
    for(int i = 0; word; i++){
        identifier += processWord(word);
        //printf("%s\n", word);
        word = strtok(NULL, " ,.;?");
    }
    if (identifier) **sentence = 0;
}  
