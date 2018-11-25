#include "text.h"
#include "sentence.h"


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

int printText(char** text){
    int i;
    for(i = 0; text[i]; i++) printf("%s\n", text[i]);
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
    struct Text text;
    readText(text);
    return 0;
}













