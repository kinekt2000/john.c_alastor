#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node{
	char c;
	struct Node* next;
	struct Node* prev;
}node;

typedef struct Stack{
	node *head;
	int count;
}stack;

void push(stack* hooks, char element);
char pop(stack* hooks);
int isempty(stack hooks);
char top(stack hooks);
char backhook(char hook);
stack create();
void freestack();


int main(){
	stack hooks = create();
	char inpC = fgetc(stdin);
	clock_t t = clock();
	for (int i = 0; i < 500000 && inpC != '\n'; i++){
		if (strchr("<({[]})>", inpC)){
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
	freestack(&hooks);
	return 0;
}


stack create(){
	stack out = {NULL, 0};
	return out;
}

void freestack(stack *hooks){
	if (hooks->count == 0) return;
	for (int i = 1; i < hooks->count; i++){
		hooks->head = hooks->head->prev;
		free(hooks->head->next);
		hooks->head->next = NULL;
	}
	free(hooks->head);
	hooks->head = NULL;
	hooks->count = 0;
}


void push(stack* hooks, char element){
	if (hooks->count == 0){
		hooks->head = (node*)malloc(sizeof(node));
		hooks->head->prev = NULL;
		hooks->head->next = NULL;
	}
	else{
		hooks->head->next = (node*)malloc(sizeof(node));
		hooks->head->next->prev = hooks->head;
		hooks->head->next->next = NULL;
		hooks->head = hooks->head->next;
	}
	hooks->head->c = element;
	hooks->count++;
}

char pop(stack* hooks){
	if (hooks->count == 0) return 0;
	char top = hooks->head->c;
	if (hooks->count == 1){
		free(hooks->head);
		hooks->head = NULL;
	}
	else{
		hooks->head = hooks->head->prev;
		free(hooks->head->next);
		hooks->head->next = NULL;
	}
	hooks->count--;
	return top;
}

int isempty(stack hooks){
	if (hooks.count) return 0;
	return 1;
}

char top(stack hooks){
	return hooks.head->c;
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
