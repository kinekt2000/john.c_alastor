#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

void readText(char ***text, int *count);
void printText(char **text, int count);
void freeText(char **text, int count);
int textcmp(const void* a, const void* b);

int main(){
	char** text;
	int count;
	readText(&text, &count);
	qsort(text, count, sizeof(char*), textcmp);
	printText(text, count);
	freeText(text, count);
	return 0;
}


void readText(char ***text, int *count){
    char input[N + 2];
    fgets(input, N + 1, stdin);
    *count = 0;
    int indic_of_sentence_start = 0;
    int current_len = 0;
    char *current_start;
    for (int i = 0; i < N; i++){
        if (indic_of_sentence_start == 0 && ( input[i] == ' ' || input[i] == '\t' )) continue;
        if (indic_of_sentence_start == 0) current_start = &(input[i]);
        indic_of_sentence_start = 1;
        current_len++;
        if (input[i] == '.'){
            if (*count == 0) *text = (char**)malloc(sizeof(char*));
            else *text = (char**)realloc(*text, ((*count)+1)*sizeof(char*));
            (*text)[*count] = (char*)calloc(current_len+1, sizeof(char));
            strncpy((*text)[*count], current_start, current_len);
            (*count) ++;
            indic_of_sentence_start = 0;
            current_len = 0;
        }
    }

}

void printText(char **text, int count){
	for(int i = 0; i < count; i++)
		printf("%s\n", text[i]);
}

void freeText(char **text, int count){
    if (count == 0) return;
    for (int i = 0; i < count; i++) free(text[i]);
	free(text);
}

int textcmp(const void* a, const void* b){
	if (strlen(*((char**)a)) > strlen(*((char**)b))) return 1;
	if (strlen(*((char**)a)) < strlen(*((char**)b))) return -1;
	return 0;
}




























