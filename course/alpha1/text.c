#include "text.h"
#include "sentence.h"


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

/*void formatText(char*** text, int f){
    switch (f){
        case 0:
            printf("%s\n", "in the pipleline");
            break;
        case 1:
            textCapitalMissing(text);
            break;
        case 2:
            ;//
        case 3:
            ;//
        default:
            printf("%s\n", "undefined function");
            break;
    }
}

int textCapitalMissing(char*** text){
    for(int i = 0; (*text)[i]; i++) formatSentenceCapitalMissing(&(*text)[i]);
    return 0;
}*/


int main(){
    FILE* file = fopen("input.txt", "r");
    struct Text input;
    readText(&input);
    printText(input);
    return 0;
}













