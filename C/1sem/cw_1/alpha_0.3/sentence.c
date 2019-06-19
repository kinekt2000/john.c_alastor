#include "sentence.h"
#define VOWELS L"EYUIOAeyuioaУАОЭЯИЮЁуаоэяиюё"
#define DEL L" ,;:'\"\\/.?!`_-"


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
    wchar_t* string = malloc(sent.memSentence*sizeof(wchar_t));
    wcscpy(string, sent.sentence);
    wchar_t* buffer;
    wchar_t* del = L" ,;:'\"\\/.?!`_-";
    wchar_t* word = wcstok(string, del, &buffer);
    for(;word;){
        if (iswlower(*word)) return 0;
        word = wcstok(buffer, del, &buffer);
    }
    free(string);
    free(buffer);
    return 1;    
}


wchar_t* vowSort(struct Sentence sent){

    int cmp(const void* a, const void* b){
        wchar_t* wordA = *(wchar_t**) a;
        //wprintf(L"%ls\n", wordA);
        wchar_t* wordB = *(wchar_t**) b;
        //wprintf(L"%ls\n", wordB);
        int countA = 0;
        int countB = 0;
        for (int i = 0; i < wcslen(wordA); i++)
            if (wcschr(VOWELS, wordA[i])) countA++;
        for (int i = 0; i < wcslen(wordB); i++)
            if (wcschr(VOWELS, wordB[i])) countB++;
        return countB - countA;
    }

    wchar_t** words = (wchar_t**) malloc(sizeof(wchar_t*));
    wchar_t* del = DEL;

    wchar_t* sentence = malloc(sent.memSentence*sizeof(wchar_t));
    wcscpy(sentence, sent.sentence);
    wchar_t* buffer;

    wchar_t* word = wcstok(sentence, del, &buffer);
    words[0] = word;
    int count;
    for (count = 1; word; count ++){
        wchar_t** wordsBuffer = (wchar_t**) realloc(words, (count+1)*sizeof(wchar_t*));
        if (wordsBuffer == NULL) return NULL; // Ошибка выделения памяти;
        else words = wordsBuffer;
        word = wcstok(buffer, del, &buffer);
        words[count] = word;
    }
    qsort(words, count-1, sizeof(wchar_t*), cmp);

    wchar_t* res = calloc(sent.memSentence, sizeof(wchar_t));
    for (int i = 0; words[i]; i++) wcscat(wcscat(res, words[i]), L" ");
    free(words);
    free(sentence);
    free(buffer);
    return res;    
}


struct Sentence wordsCount(struct Sentence sent){
    struct Sentence error = {NULL, -1, -1};
    int count;

    wchar_t** words = malloc(sizeof(wchar_t*));             // ВЫДЕЛЕННАЯ ПАМЯТЬ WORDS

    wchar_t* buffer = malloc(sent.memSentence*sizeof(wchar_t));     // выделенная память buffer
    wcscpy(buffer, sent.sentence);

    void* bufferPoint = buffer;                 // АДРЕСС НАЧАЛА BUFFERPOINT ВЫДЕЛЕННОЙ ПОД 'BUFFER' ПАМЯТИ

        // Разбиение строки на массив слов
    wchar_t* word = wcstok(buffer, DEL, &buffer);
    for(count = 0; word; count++){
        wchar_t** wordsBuffer = (wchar_t**) realloc(words, (count+1)*sizeof(wchar_t*));
        if (wordsBuffer == NULL) return error; // Ошибка выделения памяти;
        else words = wordsBuffer;
        words[count] = word;
        word = wcstok(buffer, DEL, &buffer);
    }


    int h = 0;
    wchar_t* result = calloc(1, sizeof(wchar_t));       // выделенная память под result. очистка не требуется
    int memResult = 0;
    wchar_t** repeats = malloc(sizeof(wchar_t*));       // ВЫДЕЛЕННАЯ ПАМЯТЬ ПОД ХРАНЕНИЕ ПОВТОРЯЮЩИХСЯ СЛОВ REPEATS
    for(int j = 0; j < count; j++){
        int sk = 0;     // Количество повторений
        int f = 0;      // Временная переменная для проверки на наличия слова в уже имеющемся списке повторений
        for(int k = 0; k < count; k++)
            if (wcscmp(words[j], words[k]) == 0) sk++;
        for(int d = 0; d < h; d++)
            if (wcscmp(words[j], repeats[d]) == 0) f++;
        if(sk > 1 && f == 0){
            wchar_t** repeatsBuffer = (wchar_t**) realloc(repeats, (h+1)*sizeof(wchar_t*));
            if (repeatsBuffer == NULL) return error; // Ошибка выделения памяти;
            else repeats = repeatsBuffer;
            
            int tmpSk = sk;
            int digits;
            for(digits =0; tmpSk; digits++) tmpSk /= 10;
            int currentSize = wcslen(words[j]) + 5 + digits;
            wchar_t* currentRes = malloc(currentSize*sizeof(wchar_t));      // ВЫДЕЛЕННАЯ ПАМЯТЬ ПОД ВРЕМЕННЫЙ РЕЗУЛЬТАТ CURRENTRES
            swprintf(currentRes, currentSize, L"%ls: %d; ", words[j], sk);

            memResult += currentSize;
            wchar_t* resultBuffer = (wchar_t*) realloc(result, memResult*sizeof(wchar_t*));
            if (resultBuffer == NULL) return error; // Ошибка выделения памяти;
            else result = resultBuffer;

            wcscat(result, currentRes);
            free(currentRes);       // CURRENTRES очищенна
            
            repeats[h] = words[j];
            h++; 
        }
    }
    if (memResult == 0){
        memResult = 16;
        wchar_t* resultBuffer = (wchar_t*) realloc(result, memResult*sizeof(wchar_t*));
        if (resultBuffer == NULL) return error; // Ошибка выделения памяти;
        else result = resultBuffer;

        swprintf(result, memResult, L"Повторений нет ");
    }


    result[wcslen(result)-1] = 0;
    struct Sentence out = {result, memResult, wcslen(result)};    

    free(bufferPoint);      // BUFFERPOINT (a. k. a. BUFFER) очищена
    free(repeats);          // REPEATS очищена
    free(words);            // WORDS очищена
    return out;
}





























