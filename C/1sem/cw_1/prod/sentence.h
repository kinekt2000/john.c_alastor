#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#define END L"end of file"
#define VOWELS L"EYUIOAeyuioaУАОЭЯИЮЁуаоэяиюё"// гласные для функции vowSort
#define DEL L" ,;:'\"\\/.?!`_-\n"// разделители для wcstok

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
struct Sentence strPattern(struct Sentence string);


    // Extra funcs
int cmp(const void* a, const void* b);
wchar_t* getMask(wchar_t* mask, wchar_t* word, int maxlen);

