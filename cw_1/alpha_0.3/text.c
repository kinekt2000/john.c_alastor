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
            output->text[output->sizeText] = input.text[i];
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









