#include "sentence.h"


int readSentence(struct Sentence* sent, FILE* file){

    if (file == NULL) { printf("Ошибка.\n"); return -1; } // FILE READING ERROR
    //else printf("Выполнено.\n");

    //printf("Выделение начальной памяти: ");
    sent->memSentence = 11;
    sent->sentence = (char*) malloc(sent->memSentence * sizeof(char));
    if (sent->sentence == NULL) { printf("Ошибка.\n"); return -2;} // MALLOC ERROR
    //else printf("Выполнено.\n");

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
        //if (inpC == '\n') inpC = ' ';
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

// Format sentence

/*int formatSentenceCapitalMissing(char** sentence){
    char buffer[strlen(*sentence)+1];
    strcpy(buffer, *sentence);
    char* firstWord;
    firstWord = strtok(buffer, " ,;-");
    if (islower(*firstWord)) **sentence = 0;
    return 0;
}*/

/*int main(){
    FILE* file;
    file = fopen("input.txt", "r");
    struct Sentence string1;
    struct Sentence string2;
    readSentence(&string1, file);
    readSentence(&string2, file);
    printSentence(string1);
    printSentence(string2);
    return 0;
}*/
