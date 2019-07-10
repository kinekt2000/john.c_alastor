#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct str_repeats{
	char string[102];
	int count;
}str_repeats;

typedef struct int_repeats{
	int number;
	int count;
}int_repeats;

typedef struct info{
	char teacher[102];
	char student[102];
	int group;
	char discipline[202];
}info;

typedef struct Table{
	info *data;
	int count;
}Table;

info strToInfo(const char *source);

void init_table(Table *table);
int add_to_table(Table *table, const char *teacher, const char *student, int group, const char *discipline);
void print_teachers_groups(const Table *table);


int main(){
	Table table;
	init_table(&table);

	char input[600];
	info temp;
	while(1){
		fgets(input, 598, stdin);
		input[strlen(input) - 1] = 0;
		if(!strcmp(input, "End"))break;

		temp = strToInfo(input);
		add_to_table(&table, temp.teacher, temp.student, temp.group, temp.discipline);
	}

	print_teachers_groups(&table);

	return 0;
}


void init_table(Table *table){
	table->data = NULL;
	table->count = 0;
}


info strToInfo(const char *source){
	char buffer[600];
	char *temp;
	strcpy(buffer, source);
	info dest;

	temp = strtok(buffer, ", ");
	strcpy(dest.teacher, temp);

	temp = strtok(NULL, ", ");
	strcpy(dest.student, temp);

	temp = strtok(NULL, ", ");
	dest.group = atoi(temp);

	temp = strtok(NULL, ", ");
	strcpy(dest.discipline, temp);
	return dest;
}


int add_to_table(Table *table, const char *teacher, const char *student, int group, const char *discipline){
	info *buffer;
	if(!table->count){
		buffer = malloc(sizeof(info));
		if(!buffer) return 1;
	}
	else{
		buffer = realloc(table->data, (table->count+1)*sizeof(info));
		if(!buffer) return 1;
	}
	table->data = buffer;

	strcpy(table->data[table->count].teacher, teacher);
	strcpy(table->data[table->count].student, student);
	table->data[table->count].group = group;
	strcpy(table->data[table->count].discipline, discipline);
	table->count++;
	return 0;
}


int str_cmp(const void *a, const void *b){
	str_repeats aa = *(str_repeats*)a;
	str_repeats bb = *(str_repeats*)b;
	return strcmp(aa.string, bb.string);
}

void print_teachers_groups(const Table *table){
	str_repeats buffer[100];
	int tmp_count;
	int arr_len = 0;
	for(int i = 0; i < table->count; i++){
		tmp_count = 1;
		for(int j = 0; j < table->count; j++){
			if (	!strcmp(table->data[i].teacher, table->data[j].teacher) &&
				table->data[i].group != table->data[j].group)
				tmp_count++;
		}
		int flag;
		for(flag = 0; flag < arr_len; flag++)
			if (!strcmp(table->data[i].teacher, buffer[flag].string))
				break;
		if (flag == arr_len){
			strcpy(buffer[arr_len].string, table->data[i].teacher);
			buffer[arr_len].count = tmp_count;
			arr_len++;
		}
	}

	qsort(buffer, arr_len, sizeof(str_repeats), str_cmp);

	for(int i = 0; i < arr_len; i++)
		printf("%s %d\n", buffer[i].string, buffer[i].count);
}
