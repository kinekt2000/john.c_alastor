#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

typedef struct duplicate{
	char *name;
	int count;
}string;

void repeats(char* path, string** blacklist, int* count);


int main(){
	char path[] = "./";
	string *blacklist;
	int count = 0;
	repeats(path, &blacklist, &count);

	printf("repeating files:\n");
	for (int i = 0; i < count; i++)
		if (blacklist[i].count > 1) printf("\"%s\"\n", blacklist[i].name);

	printf("\n\n");

	for (int i = 0; i < count; i++)
		printf("File \"%s\" repeats %d times\n", blacklist[i].name, blacklist[i].count);

	if(count){
		for (int i = 0; i < count; i++) free(blacklist[i].name);
		free(blacklist);
	}
	return 0;
}


void repeats(char* path, string** blacklist, int* count){
	DIR *dir = opendir(path);
	if (dir){
		struct dirent *de = readdir(dir);
		while (de){
			if (de->d_type == 4 && strcmp(de->d_name, "..") && strcmp(de->d_name, ".")){ /* is dir (not . & ..)*/
				char nested_path[100] = "";
                                strcpy(nested_path, path);
                                strcat(nested_path, "/");
                                strcat(nested_path, de->d_name);
                                repeats(nested_path, blacklist, count);
			}
			else if (de->d_type == 8){
				if ((*count) <= 0){
					*blacklist = (string*)malloc(sizeof(string));
					(*blacklist)[0].name = (char*)calloc(102, sizeof(char));
					strcpy((*blacklist)[0].name, de->d_name);
					(*blacklist)[0].count = 1;
					*count = 1;
				}
				else{
					int indicator = 0;
					for (int i = 0; i < *count; i++)
						if (strcmp((*blacklist)[i].name, de->d_name) == 0) {
							indicator = 1;
							(*blacklist)[i].count += 1;

							char filepath[100] = "";        //  Дополнительные действия для        
							strcpy(filepath, path);         //  удаления файлов
							strcat(filepath, "/");          //
							strcat(filepath, de->d_name);   //
							remove(filepath);               //

							break;
						}
					if (indicator == 0){
						string *buffer = (string*)realloc(*blacklist, ((*count)+1)*sizeof(string));
						if (buffer) *blacklist = buffer;
						else exit(1);
						(*blacklist)[*count].name = (char*)calloc(102, sizeof(char));
						strcpy((*blacklist)[*count].name, de->d_name);
						(*blacklist)[*count].count = 1;
						(*count)++;
					}
				}
			}
			de = readdir(dir);
		}
	}
	closedir(dir);
}
