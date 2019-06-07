#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#define END L"end of file"

struct Sentence{
    wchar_t* sentence;
    int memSentence;
    int sizeSentence;
};


int readSentence(struct Sentence* sentence, FILE* file);
int printSentence(struct Sentence sentence);

	// Format Sentence
int sentenceCaps(const struct Sentence sent);
wchar_t* vowSort(struct Sentence sent);
struct Sentence wordsCount(struct Sentence sent);

