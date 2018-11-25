#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define END "end of file"
#define EMPTY "file is empty"

struct Sentence{
    char* sentence;
    int memSentence;
    int sizeSentence;
};


int readSentence(struct Sentence* sentence, FILE* file);
int printSentence(struct Sentence sentence);

	// Format Sentence
int formatSentenceCapitalMissing(char** sentence);


