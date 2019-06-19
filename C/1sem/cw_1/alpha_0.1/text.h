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
int textCaps(const struct Text input, struct Text* output);
