#include <stdlib.h>
#include <stdio.h>

#define ALPHA 8
#define INPUT 7

typedef struct{
	int key;
	char data;
}pair;

typedef struct{
	pair *cells;
	int count;
}dictionary;

void init_dict(dictionary *dict);
int add_pair(dictionary *dict, int key, char data);
char return_data(dictionary *dict, int key);
void print_dict(dictionary *dict);


int main(){
	dictionary dict;
	init_dict(&dict);

	int input[7];
	int t_key;
	char t_data;

	for(int i = 0; i < ALPHA; i++){
		scanf("%d %c", &t_key, &t_data);
		add_pair(&dict, t_key, t_data);
	}
	//print_dict(&dict);
	for(int i = 0; i < INPUT; i++)
		scanf("%d", input+i);
	for(int i = 0; i < INPUT; i++)
		printf("%c", return_data(&dict, input[i]));
	printf("\n");
	return 0;
}


void init_dict(dictionary *dict){
	dict->cells = NULL;
	dict->count = 0;
}


int add_pair(dictionary *dict, int key, char data){
	pair *buffer;
	for(int i = 0; i < dict->count; i++)
		if (dict->cells[i].key == key){
			dict->cells[i].data = data;
			return 0;
		}

	if(!dict->count){
		buffer = malloc(sizeof(pair));
		if(!buffer) return 1;
	}
	else{
		buffer = realloc(dict->cells, (dict->count+1)*sizeof(pair));
		if(!buffer) return 1;
	}
	dict->cells = buffer;

	dict->cells[dict->count].key = key;
	dict->cells[dict->count].data = data;
	dict->count++;
	return 0;
}


char return_data(dictionary *dict, int key){
	for(int i = 0; i < dict->count; i++)
		if(dict->cells[i].key == key)
			return dict->cells[i].data;
	return 0;
}


void print_dict(dictionary *dict){
	printf("(");
	for(int i = 0; i < dict->count; i++){
		if(i) printf("; ");
		printf("(%d, %c)", dict->cells[i].key, dict->cells[i].data);
	}
	printf(")\n");
}


