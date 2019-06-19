#include <stdio.h>
#include <string.h>
#include <time.h>


typedef struct Stack{
	char array[2001];
	int count;
} stack;

void push(stack* hooks, char element);
char pop(stack* hooks);
int isempty(stack hooks);
char top(stack hooks);
char backhook(char hook);
stack create();

int main(){
	
	stack hooks = create();
	char inpC = fgetc(stdin);
	clock_t t = clock();
	for (int i = 0; i<500000 && inpC != '\n'; i++){
		if (strchr("<({[]})>", inpC)){
			//printf("%s\n", hooks.array);
			if (isempty(hooks)) push(&hooks, inpC);
			else{
				if (top(hooks) == backhook(inpC)) pop(&hooks);
				else push(&hooks, inpC);
			}
		}
		inpC = fgetc(stdin);
	}
	t = clock() - t;
	printf("ticks %ld, time %f sec \n", t, ((float)t)/CLOCKS_PER_SEC);
	if (isempty(hooks)) printf("correct\n");
	else printf("wrong\n");
	return 0;
}

stack create(){
	stack out = {"", 0};
	return out;
}

void push(stack* hooks, char element){
	hooks->array[hooks->count] = element;
	hooks->count++;
}

char pop(stack* hooks){
	hooks->count--;
	char top = hooks->array[hooks->count];
	hooks->array[hooks->count] = 0;
	return top;
}

int isempty(stack hooks){
	if (hooks.count) return 0;
	return 1;
}

char top(stack hooks){
	return hooks.array[hooks.count-1];
}

char backhook(char hook){
	switch (hook){
		case '(': return ')';
		case ')': return '(';
		case '[': return ']';
		case ']': return '[';
		case '{': return '}';
		case '}': return '{';
		case '<': return '>';
		case '>': return '<';
	}
	return hook;
}
