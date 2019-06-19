#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Country{
	char name[30];
	unsigned int population;
	char capital[30];
};

void readLib(struct Country **lib, int arrLen);
int structCmp(const void *pa, const void *pb);


int main(){
	int arrLen;
        struct Country *lib;

        scanf("%d", &arrLen);
        readLib(&lib, arrLen);
	qsort(lib, arrLen, sizeof(struct Country), structCmp);
	for(int i = 0; i < arrLen; i++)
		printf("%s %u %s ", lib[i].name, lib[i].population, lib[i].capital);
	free(lib);
	return 0;
}


void readLib(struct Country **lib, int arrLen){
	if (arrLen == 0) return;
	*lib = (struct Country*)malloc(sizeof(struct Country)*arrLen);
	for(int i = 0; i < arrLen; i++)
		scanf("%s %u %s", (*lib)[i].name, &((*lib)[i].population), (*lib)[i].capital);
}


int structCmp(const void *pa, const void *pb){
	struct Country a = *((struct Country*)pa);
	struct Country b = *((struct Country*)pb);
	int bl = strcmp(a.name, b.name);
	if (bl) return bl;
	if (a.population > b.population) return 1;
	if (a.population < b.population) return -1;
	return 0;
}
