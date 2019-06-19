#include "sentence.h"

    // INPUT OUTPUT 

int readSentence(struct Sentence* sent, FILE* file){

    if (file == NULL) { printf("Ошибка.\n"); return -1; } // FILE READING ERROR

    sent->memSentence = 11;
    sent->sentence = (char*) malloc(sent->memSentence * sizeof(char));
    if (sent->sentence == NULL) { printf("Ошибка.\n"); return -2;} // MALLOC ERROR

    char inpC;
    do								// Считывание пустых символов
        inpC = fgetc(file);					// в начале предложения
    while(inpC == ' ' || inpC == '\t' || inpC == '\n');

    *(sent->sentence) = inpC;
    for(sent->sizeSentence = 1; inpC != '.' && inpC != '?' && inpC != '!' && inpC != EOF; sent->sizeSentence++){
		    // Выделение памяти по надобности
        if (sent->sizeSentence % 10 == 0){
            sent->memSentence += 10;
            char* sentenceBuff = (char*) realloc(sent->sentence, sent->memSentence * sizeof(char));
            if (sentenceBuff == NULL) { printf("Ошибка расширения памяти.\n"); return -3; } // SENTENCE REALLOC ERROR
            else sent->sentence = sentenceBuff;
        }
        inpC = fgetc(file);
        (sent->sentence)[sent->sizeSentence] = inpC;
        (sent->sentence)[sent->sizeSentence + 1] = 0;
    }
    
    if (inpC == EOF){
        free(sent->sentence);
        sent->sentence = END;
    }

    return 0;
}

int printSentence(struct Sentence sent){
    puts(sent.sentence);
    return 0;
}


    // FORMAT 

int sentenceCaps(const struct Sentence sent){
    char* buffer = malloc(sent.sizeSentence*sizeof(char));
    strcpy(buffer, sent.sentence);
    char* del = " ,;:'\"\\/.?!`_-";
    char* word = strtok(buffer, del);
    for(;word;){
        if (*word != toupper(*word)) return 0;
        word = strtok(NULL, del);
    }
    return 1;    
}



/*int main(){
    struct Sentence string = {"ONE TWO THREE FOUR", 21, 16};
    vowSort(string);    
    return 0;
}*/






