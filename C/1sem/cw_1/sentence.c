#include "sentence.h"

struct Sentence{
    char* sentence;
    int memSentence;
    int sizeSentence;
};

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

// Format sentence

int formatSentenceCapitalMissing(char** sentence){
    char buffer[strlen(*sentence)+1];
    strcpy(buffer, *sentence);
    char* firstWord;
    firstWord = strtok(buffer, " ,;-");
    if (islower(*firstWord)) **sentence = 0;
    return 0;
}
