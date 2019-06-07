#include <stdlib.h>
#include <stdio.h>


struct Text{
    struct Sentence* text;
    int memText;
    int sizeText;
};

int readText(struct Text* text);
int printText(struct Text text);

	// Format text
void formatText(char*** text, int f);
int textCapitalMissing(char*** text);
