#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackArray{
	int *array;
	int count;
	int err;
}stackArray;

int push(stackArray *stack, int element);
int pop(stackArray *stack);
int top(stackArray* stack);
int size(stackArray* stack);
stackArray init();
void freestack(stackArray *stack);

int roundstack(stackArray *stack);
int funcNum(char *cmd);

int main(){
	stackArray stack = init();
	int finish = roundstack(&stack);
	freestack(&stack);
	if (finish) { printf("error\n"); return 0; }
	printf("bye\n");
	return 0;
}


stackArray init(){
	stackArray stack = {NULL, 0, 0};
	return stack;
}


int roundstack(stackArray *stack){
	int elem; // for Push, Pop 'n' top;
	int ind = 0; // errors indication
	char cmd[6];
	fgets(cmd, 5, stdin);
	while(strcmp(cmd, "exit")){
		for (int i = strlen(cmd)-1; cmd[i] == ' ' || cmd[i] == '\n'; i-- ) cmd[i] = 0;
		int cmdNum = funcNum(cmd);
		switch (cmdNum){
			case 1:
				ind = scanf("%d", &elem);
				//printf("%d\n", elem);
				if (ind == 0) { freestack(stack); return 1; }
				push(stack, elem);
				if (stack->err) { freestack(stack); return 1; }
				printf("ok\n");
				fgetc(stdin);
				break;
			case 2:
				elem = pop(stack);
				if (stack->err) { freestack(stack); return 1; }
				printf("%d\n", elem);
				break;
			case 3:
				elem = top(stack);
				if (stack->err) { freestack(stack); return 1;}
				printf("%d\n", elem);
				break;
			case 4:
				printf("%d\n", size(stack));
				fgetc(stdin);
				break;
			case 5:
				break;
			default:
				return 1;
				break;
		}
		fgets(cmd, 5, stdin);
	}
	return 0;
}


int push(stackArray *stack, int element){
	if (stack->count == 0){
		stack->array = (int*)malloc(sizeof(int));
		if (stack->array == NULL){
			stack->err = 1;
			return 0;
		}
	}
	else{
		int* buffer = (int*)realloc(stack->array, (stack->count+1)*sizeof(int));
		if (buffer == NULL){
			stack->err = 1;
			return 0;
		}
		stack->array = buffer;
	}
	stack->array[stack->count] = element;
	stack->count++;
	stack->err = 0;
	return 0;
}


int pop(stackArray *stack){
	if (stack->count == 0){
		stack->err = 1;
		return 0;
	}
	int out = stack->array[stack->count - 1];
	if (stack->count == 1){
		free(stack->array);
	}
	else if (stack->count > 1){
		int* buffer = (int*)realloc(stack->array, sizeof(int)*(stack->count - 1));
		if ((buffer) == NULL){
			stack->err = 1;
			return 0;
		}
		stack->array = buffer;
	}
	stack->count--;
	stack->err = 0;
	return out;
}


int top(stackArray *stack){
	if (stack->count == 0) { stack->err = 1; return 0; }
	printf("debug\n");
	return stack->array[stack->count - 1];
}


int size(stackArray *stack){
	return stack->count;
}

int funcNum(char* cmd){
	if (strcmp(cmd, "push") == 0) return 1;
	if (strcmp(cmd, "pop") == 0) return 2;
	if (strcmp(cmd, "top") == 0) return 3;
	if (strcmp(cmd, "size") == 0) return 4;
	if (strcmp(cmd, "exit") == 0) return 5;
	return 0;
}

void freestack(stackArray *stack){
	if (stack->count == 0) return;
        free(stack->array);
        stack->count = 0;
}
