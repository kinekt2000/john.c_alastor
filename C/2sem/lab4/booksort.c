#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Book{
	char name[30];
	char author[30];
	unsigned int pages;
	char isbn[20];
};

void readLib(struct Book **lib, int arrLen);
int structCmp(const void *pa, const void *pb);

int main(){
	int arrLen;
	struct Book *lib;

	scanf("%d", &arrLen);
	readLib(&lib, arrLen);
	qsort(lib, arrLen, sizeof(struct Book), structCmp);
	for(int i = 0; i < arrLen; i++)
		printf("%s %s %u %s ", lib[i].name, lib[i].author, lib[i].pages, lib[i].isbn);
	free(lib);
	return 0;
}


void readLib(struct Book **lib, int arrLen){
	if (arrLen == 0) return;
	*lib = (struct Book*)malloc(sizeof(struct Book)*arrLen);
	for (int i = 0; i < arrLen; i++)
		scanf("%s %s %u %s", (*lib)[i].name, (*lib)[i].author, &((*lib)[i].pages), (*lib)[i].isbn);
}

int structCmp(const void *pa, const void *pb){
	struct Book a = *((struct Book*)pa);
	struct Book b = *((struct Book*)pb);
	return strcmp(a.author, b.author);
}
