#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count(char* instr){
	char* str = (char*)malloc(202);
	char* point_str = str;
	strcpy(str, instr);
	char* lex = strtok(str, " \n");

	char words[50][50];
	int count;

	for (count = 0; lex != NULL; count++){
		strcpy(words[count], lex);
		lex = strtok(NULL, " \n");
	}
	free(point_str);

	count++;
	int maxrepeats = 0;
	for(int i = 0; i < count; i++){
		int repeats = 0;
		for(int j = 0; j < count; j++)
			if (strcmp(words[i], words[j]) == 0) repeats++;
		if (repeats > maxrepeats) maxrepeats = repeats;
	}
	return maxrepeats;
}


int main(){
	char str[202];
	fgets(str, 200, stdin);
	int cnt = count(str);
	printf("%d\n", cnt);
	return 0;
}
