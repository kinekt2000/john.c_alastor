#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 200

int str_cmp(const void* a, const void* b);
int count(const char* input);


int main(){

	char string[LEN+2];
	fgets(string, LEN, stdin);
	int res = count(string);
	printf("%d\n", res);
	return 0;
}


int count(const char* input){
	char *string = (char*)malloc((LEN+2)*sizeof(char));
	char *string_p = string;
	strncpy(string, input, LEN);

	char **words_arr = (char**)calloc((LEN+2),sizeof(char*));

	char* word = strtok(string, " \n");
	int cnt_of_words;
	for(cnt_of_words = 0; word; cnt_of_words++){
		words_arr[cnt_of_words] = (char*)malloc((LEN/4 + 2)*sizeof(char));
		strncpy(words_arr[cnt_of_words], word, LEN/4);
		word = strtok(NULL, " \n");
	}

	qsort(words_arr, cnt_of_words, sizeof(char*), str_cmp);

	int max = 0;
	int i;
	for(i = 0; i < cnt_of_words;){
		int j;
		for(j = i; words_arr[j] && !strcmp(words_arr[i], words_arr[j]); j++);
		if ((j - i) > max) max = j - i;
		i = j;
	}

	for(int i = 0; i < cnt_of_words; i++)
		free(words_arr[i]);
	free(words_arr);
	return max;
}


int str_cmp(const void* a, const void* b){
	char** str1_p = (char**)a;
	char** str2_p = (char**)b;
	return strcmp(*str1_p, *str2_p);
}
