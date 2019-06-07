#include "sentence.h"
#define VOWELS "EYUIOAeyuioaУАОЭЯИЮЁуаоэяиюё"


    // INPUT OUTPUT 

int readSentence(struct Sentence* sent, FILE* file){
    setlocale(LC_CTYPE, "");

    if (file == NULL) { wprintf(L"Ошибка.\n"); return -1; } // FILE READING ERROR

    sent->memSentence = 11;
    sent->sentence = (wchar_t*) malloc(sent->memSentence * sizeof(wchar_t));
    if (sent->sentence == NULL) { wprintf(L"Ошибка.\n"); return -2;} // MALLOC ERROR

    wchar_t inpC;
    do								// Считывание пустых символов
        inpC = fgetwc(file);					// в начале предложения
    while(inpC == L' ' || inpC == L'\t' || inpC == L'\n');

    *(sent->sentence) = inpC;
    for(sent->sizeSentence = 1; inpC != L'.' && inpC != L'?' && inpC != L'!' && inpC != WEOF; sent->sizeSentence++){
		    // Выделение памяти по надобности
        if (sent->sizeSentence % 10 == 0){
            sent->memSentence += 10;
            wchar_t* sentenceBuff = (wchar_t*) realloc(sent->sentence, sent->memSentence * sizeof(wchar_t));
            if (sentenceBuff == NULL) { wprintf(L"Ошибка расширения памяти.\n"); return -3; } // SENTENCE REALLOC ERROR
            else sent->sentence = sentenceBuff;
        }
        inpC = fgetwc(file);
        (sent->sentence)[sent->sizeSentence] = inpC;
        (sent->sentence)[sent->sizeSentence + 1] = 0;
    }
    
    if (inpC == WEOF){
        free(sent->sentence);   
        sent->sentence = END;
    }

    return 0;
}

int printSentence(struct Sentence sent){
    wprintf(L"%ls\n", sent.sentence);
    return 0;
}


    // FORMAT 

int sentenceCaps(const struct Sentence sent){
    wchar_t* buffer = malloc(sent.sizeSentence*sizeof(wchar_t));
    wcscpy(buffer, sent.sentence);
    wchar_t* del = L" ,;:'\"\\/.?!`_-";
    wchar_t* word = wcstok(buffer, del);
    for(;word;){
        if (iswlower(*word)) return 0;
        word = wcstok(NULL, del);
    }
    return 1;    
}


/* char* vowSort(struct Sentence sent){

    int cmp(const void* a, const void* b){
        char* wordA = *(char**) a;
        //printf("%s\n", wordA);
        char* wordB = *(char**) b;
        //printf("%s\n", wordB);
        int countA = 0;
        int countB = 0;
        for (int i = 0; i < strlen(wordA); i++)
            if (strchr(VOWELS, wordA[i])) countA++;
        for (int i = 0; i < strlen(wordB); i++)
            if (strchr(VOWELS, wordB[i])) countB++;
        return countB - countA;
    }

    char** words = (char**) malloc(sizeof(char*));
    char* del = " ,;:'\"\\/.?!`_-";

    char* sentence = malloc(sent.sizeSentence*sizeof(char));
    strcpy(sentence, sent.sentence);

    char* word = strtok(sentence, del);
    words[0] = word;
    int count;
    for (count = 1; word; count ++){
        char** buffer = (char**) realloc(words, (count+1)*sizeof(char*));
        if (buffer == NULL) return NULL; // Ошибка выделения памяти;
        else words = buffer;
        word = strtok(NULL, del);
        words[count] = word;
    }
    qsort(words, count-1, sizeof(char*), cmp);
    
    for (int i = 0; words[i]; i++){
        printf("%s\n", words[i]);
    }

    char* res = calloc(sent.memSentence, sizeof(char));
    for (int i = 0; words[i]; i++) strcat(strcat(res, words[i]), " ");
    *strrchr(res, ' ') = 0;
    return res;    
}*/


/*int main(){
    struct Sentence s = {"Hello, what is ur name?", 30, 22};
    printf("%s\n",vowSort(s));
    return 0;
}*/




