#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	char key[100];
	char data[100];
}pair;

typedef struct{
	pair *cells;
	int count;
}dictionary;


dictionary init_dict();
int add_pair(dictionary *dict, const char *key, const char *data);
char* return_data(dictionary *dict, const char *key);
void remove_pair(dictionary *dict, const char *key);
int isEmpty(dictionary *dict);

int main(){
	dictionary dict = init_dict();
	printf("%d\n", isEmpty(&dict));

	add_pair(&dict, "key", "data");
	add_pair(&dict, "key2", "data2");
	add_pair(&dict, "key3", "data3");
	add_pair(&dict, "key4", "data4");
	add_pair(&dict, "key", "cdata");
	printf("%d\n", isEmpty(&dict));

	char *out = return_data(&dict, "key2");

	if (out) puts(out);
	else puts("there is no key");

	remove_pair(&dict, "key2");
	out = return_data(&dict, "key2");

	if (out) puts(out);
        else puts("there is no key");
	return 0;
}


dictionary init_dict(){
        dictionary out;
        out.cells = NULL;
        out.count = 0;
        return out;
}


int add_pair(dictionary *dict, const char *key, const char *data){
	pair *buffer;
	for(int i = 0; i < dict->count; i++)
		if(strcmp(dict->cells[i].key, key) == 0){
			strcpy(dict->cells[i].data, data);
			return 0;
		}


	if (strlen(key) > 99 || strlen(data) > 99)
		return 1;

	if (!dict->count){
		buffer = malloc(sizeof(pair));
		if (!buffer) return 2;
		dict->cells = buffer;
		dict->count = 1;
	}
	else{
		buffer = realloc(dict->cells, (dict->count+1)*sizeof(pair));
		if (!buffer) return 2;
		dict->cells = buffer;
		dict->count++;
	}

	strcpy(dict->cells[dict->count - 1].key, key);
	strcpy(dict->cells[dict->count - 1].data, data);
	return 0;
}


char* return_data(dictionary *dict, const char *key){
	for(int i = 0; i < dict->count; i++){
		if (!strcmp(dict->cells[i].key, key))
			return dict->cells[i].data;
	}
	return 0;
}


void remove_pair(dictionary *dict, const char *key){
	for (int i = 0; i < dict->count; i++)
		if (!strcmp(dict->cells[i].key, key)){
			if(dict->count == 1)
				free(dict->cells);
			else{
				for (int j = i + 1; j < dict->count; j++)
					dict->cells[j - 1] = dict->cells[j];
				dict->cells = realloc(dict->cells, (dict->count - 1)*sizeof(pair));
			}
			dict->count--;
			return;
		}
}


int isEmpty(dictionary * dict){
	if (dict->count)
		return 1;
	return 0;
}
