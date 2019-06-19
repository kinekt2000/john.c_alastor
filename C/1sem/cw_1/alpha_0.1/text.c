#include "text.h"
#include "sentence.h"

    // INPUT OUTPUT

int readText(struct Text* text){

    printf("Открытие файла: ");
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) { printf("Ошибка.\n"); return -1;}
    else printf("Выполнено\n");

    text->memText = 6;
    text->text = (struct Sentence*) malloc(text->memText * sizeof(struct Sentence));

    readSentence(&(text->text)[0], file);

    for(text->sizeText = 1; strcmp((text->text)[text->sizeText-1].sentence, END); text->sizeText++){
		// Выделение памяти по надобности.
        if (text->sizeText % 5 == 0){
            text->memText += 5;
            struct Sentence* textBuff = (struct Sentence*) realloc(text->text, text->memText * sizeof(struct Sentence));
            if (textBuff == NULL) return -1; // -1 - TEXT REALLOC ERROR
            else text->text = textBuff;
        }
        readSentence(&((text->text)[text->sizeText]), file);
        (text->text)[text->sizeText + 1].sentence = NULL;
    }
    printf("Чтение файла закончено\n");

    printf("Закрытие файла: ");
    if ( fclose (file) == EOF) printf ("Ошибка\n");
    else printf ("Выполнено\n");

    if(text->sizeText == 1){
        (text->text)[0].sentence = "file is empty";
    } 

    return text->sizeText;
}

int printText(struct Text text){
    int i;
    for(i = 0; text.text[i].sentence; i++) printSentence(text.text[i]);
    return i;
}


    // FORMAT

int textCaps(const struct Text input, struct Text* output){
    output->memText = 1;
    output->sizeText = 0;
    struct Sentence* buffer = malloc(sizeof(struct Sentence));
    if (buffer == NULL) { printf("Ошибка выделения памяти\n"); return -1;}
    else output->text = buffer;
    for (int i = 0; i < input.sizeText-1; i++){
        if (sentenceCaps(input.text[i])){
            output->memText++;
            buffer = realloc(output->text, output->memText*sizeof(struct Sentence));
            if (buffer == NULL) { printf("Ошибка расширения памяти\n"); return -1; }
            else output->text = buffer;
            output->text[output->sizeText] = input.text[i];
            output->sizeText++;
        }
    }
    output->text[output->sizeText] = input.text[input.sizeText-1];
    printf("end\n");
    return 0;
}













