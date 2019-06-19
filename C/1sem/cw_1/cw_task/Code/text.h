#include <stdlib.h>
#include <stdio.h>


struct Text{
    struct Sentence* text;
    int memText;
    int sizeText;
};

int sentenceTest(struct Sentence sent, struct Text text);
int readText(struct Text* text);
int printText(struct Text text);

	// Format text
int cleanText(struct Text format);
int textCaps(const struct Text input, struct Text* output);
int textVowSort(const struct Text input, struct Text* output);
int textWordsCount(const struct Text input, struct Text* output);
int textPattern(const struct Text input, struct Text* output);
int textAnn(struct Text input, struct Text* output);
