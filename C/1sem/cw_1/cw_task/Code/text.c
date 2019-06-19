#include "text.h"
#include "sentence.h"

    // INPUT OUTPUT
int sentenceTest(struct Sentence sent, struct Text text)
    {
    int count = 0;
    for (int i = 0; i < text.sizeText; i++){
        if (sent.sizeSentence != text.text[i].sizeSentence) continue;
        for (int j = 0; j < sent.sizeSentence; j++){
            if (towupper(sent.sentence[j]) != towupper(text.text[i].sentence[j])) break;
        }
    count++;
    }
    if (count) return 1;
    else return 0;
}


int readText(struct Text* text){
    setlocale(LC_CTYPE, "");

    wprintf(L"Открытие файла: ");
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) { wprintf(L"Ошибка.\n"); return -1;}
    else wprintf(L"Выполнено\n");

    text->memText = 6;
    text->text = (struct Sentence*) malloc(text->memText * sizeof(struct Sentence));

    readSentence(&(text->text)[0], file);

    for(text->sizeText = 1; wcscmp((text->text)[text->sizeText-1].sentence, END); text->sizeText++){
		// Выделение памяти по надобности.
        if (text->sizeText % 5 == 0){
            text->memText += 5;
            struct Sentence* textBuff = (struct Sentence*) realloc(text->text, text->memText * sizeof(struct Sentence));
            if (textBuff == NULL) return -1; // -1 - TEXT REALLOC ERROR
            else text->text = textBuff;
        }
        struct Sentence tmp;
        readSentence(&tmp, file);
        int i = sentenceTest(tmp, *text);
        if (i) text->sizeText--;
        else text->text[text->sizeText] = tmp;
        //readSentence(&((text->text)[text->sizeText]), file);
        (text->text)[text->sizeText + 1].sentence = NULL;
    }
    wprintf(L"Чтение файла закончено\n");

    wprintf(L"Закрытие файла: ");
    if (fclose (file) == WEOF) wprintf(L"Ошибка\n");
    else wprintf (L"Выполнено\n");

    if(text->sizeText == 1){
        (text->text)[0].sentence = L"file is empty";
    } 

    return text->sizeText;
}


int printText(struct Text text){
    int i;
    for(i = 0; i < text.sizeText/*text.text[i].sentence*/; i++) printSentence(text.text[i]);
    return i;
}


    // FORMAT
int cleanText(struct Text format){
    for(int i = 0; i < format.sizeText-1; i++) free(format.text[i].sentence);
    free(format.text);
    return 0;
}


int textCaps(const struct Text input, struct Text* output){
    output->memText = 1;
    output->sizeText = 0;
    wprintf(L"Выделение памяти: ");
    struct Sentence* buffer = malloc(sizeof(struct Sentence));
    if (buffer == NULL) { wprintf(L"Ошибка\n"); return -1;}
    else { output->text = buffer; wprintf(L"Выполнено\n"); }
    wprintf(L"Форматирование: ");
    for (int i = 0; i < input.sizeText-1; i++){
        if (sentenceCaps(input.text[i])){
            output->memText++;
            buffer = realloc(output->text, output->memText*sizeof(struct Sentence));
            if (buffer == NULL) { wprintf(L"Ошибка\n"); return -1; }
            else output->text = buffer;
            //output->text[output->sizeText] = input.text[i];
            output->text[output->sizeText].memSentence = input.text[i].memSentence;
            output->text[output->sizeText].sizeSentence = input.text[i].sizeSentence;
            wchar_t* strBuffer = malloc(input.text[i].memSentence * sizeof(wchar_t));
            if (strBuffer == NULL) { wprintf(L"Ошибка\n"); return -1; }
            output->text[output->sizeText].sentence = strBuffer;
            wcscpy(output->text[output->sizeText].sentence, input.text[i].sentence);
            output->sizeText++;
        }
    }
    wprintf(L"Выполнено\n");
    output->text[output->sizeText++] = input.text[input.sizeText-1];
    return 0;
}


int textVowSort(const struct Text input, struct Text* output){
    output->memText = input.memText;
    output->sizeText = input.sizeText;
    wprintf(L"Выделение памяти: ");
    struct Sentence* buffer = malloc(output->memText*sizeof(struct Sentence));
    if (buffer == NULL) { wprintf(L"Ошибка\n"); return -1; }
    else output->text = buffer; wprintf(L"Выполнено\n");
    wprintf(L"Форматирование: ");
    for(int i =0; i < input.sizeText-1; i++)
        output->text[i].sentence = vowSort(input.text[i]);
    output->text[output->sizeText-1].sentence = END;
    wprintf(L"Выполнено\n");
    return 0;
}


int textWordsCount(const struct Text input, struct Text* output){
    output->memText = input.memText;
    output->sizeText = input.sizeText;
    wprintf(L"Выделение памяти: ");
    struct Sentence* buffer = malloc(output->memText*sizeof(struct Sentence));
    if (buffer == NULL) { wprintf(L"Ошибка\n"); return -1; }
    else output->text = buffer; wprintf(L"Выполнено\n");
    wprintf(L"Форматирование: ");
    for(int i =0; i < input.sizeText-1; i++){
        output->text[i] = wordsCount(input.text[i]);
    }
    output->text[output->sizeText-1].sentence = END;
    wprintf(L"Выполнено\n");
    return 0;
}


int textPattern(const struct Text input, struct Text* output){
    //setlocale(LC_CTYPE, "");
    output->memText = input.memText;
    output->sizeText = input.sizeText;
    wprintf(L"Выделение памяти: ");
    struct Sentence* buffer = malloc(output->memText*sizeof(struct Sentence));
    if (buffer == NULL) { wprintf(L"Ошибка\n"); return -1; }
    else output->text = buffer; wprintf(L"Выполнено\n");
    wprintf(L"Форматирование: ");
    for(int i =0; i < input.sizeText-1; i++){
        output->text[i] = strPattern(input.text[i]);
    }
    output->text[output->sizeText-1].sentence = END;
    wprintf(L"Выполнено\n");
    return 0;
}

int annCmp(const void* a, const void* b){
    return *(wchar_t*)b - *(wchar_t*)a;
}


int textAnn(struct Text input, struct Text* output){
    wchar_t** words = malloc(sizeof(wchar_t*));
    int count = 0;
    for (int i = 0; i < input.sizeText - 1; i++){
        wchar_t* buffer = malloc(input.text[i].memSentence * sizeof(wchar_t));
        wcscpy(buffer, input.text[i].sentence);
        void* bufferPoint = buffer;

        wchar_t* word = wcstok(buffer, DEL, &buffer);
        int j;
        for (; word; count++){
            wchar_t** wordsBuffer = (wchar_t**) realloc(words, (count+1)*sizeof(wchar_t*));
            if (wordsBuffer == NULL) return -1; // Ошибка выделения памяти;
            else words = wordsBuffer;
            for(int j = 0; j < wcslen(word); j++) word[j] = towlower(word[j]);
            words[count] = word;
            word = wcstok(buffer, DEL, &buffer);
        }
        count;
    }

    int h = 0;
    wchar_t* result = malloc(sizeof(wchar_t));      
    int memResult = 0;
    wchar_t** repeats = calloc(1, sizeof(wchar_t*));       
    for(int j = 0; j < count; j++){
        if(words[j][0] == L'\n') continue;
        wchar_t* tmpCurrWord = malloc((wcslen(words[j])+1) * sizeof(wchar_t));
        wcscpy(tmpCurrWord, words[j]);
        qsort(tmpCurrWord, wcslen(tmpCurrWord), sizeof(wchar_t), annCmp);
        int sk = 0;     // Количество повторений
        int f = 0;      // Временная переменная для проверки на наличия слова в уже имеющемся списке повторений
        for(int k = 0; k < count; k++){
            wchar_t* tmpWord = malloc((wcslen(words[k])+1) * sizeof(wchar_t));
            wcscpy(tmpWord, words[k]);
            qsort(tmpWord, wcslen(tmpWord), sizeof(wchar_t), annCmp);
            if (wcscmp(tmpCurrWord, tmpWord) == 0) sk++;
            free(tmpWord);
        }

        for(int d = 0; d < h; d++){
            if (wcscmp(words[j], repeats[d]) == 0) f++;
        }

        if(sk > 1 && f == 0){
            wchar_t** repeatsBuffer = (wchar_t**) realloc(repeats, (h+1)*sizeof(wchar_t*));
            if (repeatsBuffer == NULL) return -1; // Ошибка выделения памяти;
            else repeats = repeatsBuffer;
            int tmpSk = sk;
            int digits;
            for(digits =0; tmpSk; digits++) tmpSk /= 10;
            int currentSize = wcslen(words[j]) + 5 + digits;
            wchar_t* currentRes = malloc(currentSize * sizeof(wchar_t));      // ВЫДЕЛЕННАЯ ПАМЯТЬ ПОД ВРЕМЕННЫЙ РЕЗУЛЬТАТ CURRENTRES
            swprintf(currentRes, currentSize, L"%ls: %d; ", words[j], sk);
            memResult += currentSize;
            wchar_t* resultBuffer = (wchar_t*) realloc(result, memResult*sizeof(wchar_t));
            if (resultBuffer == NULL) return -1; // Ошибка выделения памяти;
            result = resultBuffer;
            wcscat(result, currentRes);
            free(currentRes);       // CURRENTRES очищенна
            repeats[h] = words[j];
            h++;
        }
    free(tmpCurrWord);
    }

    if (memResult == 0){
        wprintf(L"ok\n");
        memResult = 16;
        wchar_t* resultBuffer = (wchar_t*) realloc(result, memResult*sizeof(wchar_t));
        if (resultBuffer == NULL) return -1; // Ошибка выделения памяти;
        else result = resultBuffer;

        swprintf(result, memResult, L"Повторений нет ");
    }

    output->memText = 1;
    output->sizeText = 1;
    output->text = malloc(sizeof(struct Sentence));
    output->text[0].sentence = result;
    output->text[0].memSentence = memResult;
    output->text[0].sizeSentence = wcslen(result);

    return 0;
}


























