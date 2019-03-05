#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>


void content(char* path, char ***cont, int *count);
int cmp(const void *a, const void *b);

int main(){
	char **cont;
	int count = 0;
	char path[] = "./";
	content(path, &cont, &count);
	printf("%d\n", count);
	for(int i = 0; i < count; i++)
		printf("%s", cont[i]);

	qsort(cont, count, sizeof(char*), cmp);
	printf("\nSorted\n");

	for(int i = 0; i < count; i++)
                printf("%s", cont[i]);

	FILE *result = fopen("./result.txt", "wb");
	for(int i = 0; i < count; i++)
		fprintf(result, "%s", cont[i]);
	fclose(result);

	if(count){
		for(int i = 0; i < count; i++) free(cont[i]);
		free(cont);
	}
	return 0;
}


int cmp(const void* a, const void *b){
	char *strA = *(char**)a;
	char *strB = *(char**)b;
	long int numA;
	long int numB;
	sscanf(strA, "%ld", &numA);
	sscanf(strB, "%ld", &numB);
	if (numA < numB) return -1;
	if (numA == numB) return 0;
	return 1;
}


void content(char *path, char ***cont, int *count){
	DIR *dir = opendir(path);
	if (dir){
		struct dirent *de = readdir(dir);
		while(de){
			if (de->d_type == 4 && strcmp(de->d_name, "..") && strcmp(de->d_name, ".")){ /* is dir (not . & ..)*/
				printf("open this directory: %s\n", de->d_name);
				char nested_path[100] = "";
				strcpy(nested_path, path);
				strcat(nested_path, "/");
				strcat(nested_path, de->d_name);
				content(nested_path, cont, count);
			}
			else if (de->d_type == 8 && strcmp(de->d_name+strlen(de->d_name)-4, ".txt")==0){

				/*
					Программа создает и заполняет массив названиями файлов, которые кончаются на .txt
					Нужно с помощью fopen открывать файл path+d_name и сохранить первую строку оттуда в
					char info[100] и уже  заполнять массив не именами, а содержимым
				*/

				char* sent = (char*)calloc(102, sizeof(char));
				char txtpath[100] = "";
				strcpy(txtpath, path);
				strcat(txtpath, "/");
				strcat(txtpath, de->d_name);
				FILE *txt = fopen(txtpath, "r");
				fgets(sent, 100, txt);
				fclose(txt);
				if (!(*count)) *cont = (char**)malloc(sizeof(char*));
                                else{
                                        char **buffer = (char**)realloc(*cont, ((*count)+1)*sizeof(char*));
                                        if (buffer) *cont = buffer;
                                        else exit(1);
                                }
				(*cont)[*count] = sent;

				/*char* name = (char*)calloc(strlen(de->d_name)+2, sizeof(char));
				strcpy(name, de->d_name);
				strcat(name, "\n");
				if (!(*count)) *cont = (char**)malloc(sizeof(char*));
				else{
					char **buffer = (char**)realloc(*cont, ((*count)+1)*sizeof(char*));
					if (buffer) *cont = buffer;
					else exit(1);
				}
				(*cont)[*count] = name;*/

				(*count)++;
			}
			de = readdir(dir);
		}
	}
	closedir(dir);
}

