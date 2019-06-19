#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N 202

int cmp(const void* a, const void* b){
return strcmp(*((const char**)a), *((const char**)b));
}

int count(const char* input){
char text[N];
strcpy(text, input);
int num = 0;
char* word_arr[N];
char* tok = strtok(text, " \n");
while(tok){
word_arr[num] = tok;
num++;
tok = strtok(NULL, " \n"); 
}

qsort(word_arr, num, sizeof(char*), cmp);

int max = 0;
int i = 0;
while(i<(num-1)){
int count = 0;
int j = i+1;

if(!strcmp(word_arr[i], word_arr[j])) count+=2;
while((j+1<num) && (!strcmp(word_arr[i], word_arr[j+1]))){
j++;
count++;
}
if(count>max) max = count;
i = j;
}
return max;
}

int main() {
char text[N];
fgets(text, N, stdin);
printf("%d\n", count(text));

//char text1[N] = "mw wue minpvrxnos aivedg mqfpv pbhlzfpi zj l ri yopzw tnxy sy u rgrklr y hkxs mpbjyk mswm y dheydp m r zeicyqgyif";
//char text2[N] = "mw wue wue aivedg mqfpv pbhlzfpi zj l ri yopzw tnxy sy u rgrklr y y hkxs mpbjyk mswm y dheydp m r zeicyqgyif";
//assertEqual(count(text1), 2);
//assertEqual(count(text2), 3);
return 0;
}
