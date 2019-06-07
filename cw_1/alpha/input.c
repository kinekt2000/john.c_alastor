//READY!
#include "input.h"


int readText(char*** text){
    int memText = 6;
    *text = (char**) malloc(memText * sizeof(char*));

    readSentence(*text);

    int sizeText;
    for(sizeText = 1; strcmp((*text)[sizeText-1], STOP); sizeText++){
		// Выделение памяти по надобности.
        if (sizeText % 5 == 0){
            memText += 5;
            char** textBuff = (char**) realloc(*text, memText * sizeof(char*));
            if (textBuff == NULL) return -1; // -1 - TEXT REALLOC ERROR
            else *text = textBuff;
        }
        readSentence(&(*text)[sizeText]);
        (*text)[sizeText + 1] = NULL;
    }
    return sizeText;
}


int readSentence(char** sentence){
    int memSentence = 11;
    *sentence = (char*) malloc(memSentence * sizeof(char));
    char inpC;
    do								// Считывание пустых символов
        inpC = fgetc(stdin);					// в начале предложения
    while(inpC == ' ' || inpC == '\t' || inpC == '\n');
    **sentence = inpC;

    int sizeSentence;
    for(sizeSentence = 1; inpC != '.' && inpC != '?' && inpC != '!'; sizeSentence++){
		// Выделение памяти по надобности
        if (sizeSentence % 10 == 0){
            memSentence += 10;
            char* sentenceBuff = (char*) realloc(*sentence, memSentence * sizeof(char));
            if (sentenceBuff == NULL) return -2; // -2 - SENTENCE REALLOC ERROR
            else *sentence = sentenceBuff;
        }
        inpC = fgetc(stdin);
        if (inpC == '\n') inpC = ' ';
        (*sentence)[sizeSentence] = inpC;
        (*sentence)[sizeSentence + 1] = 0;
    }
    return 0;
}
