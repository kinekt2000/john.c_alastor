#include <stdio.h>

#define N 5

typedef struct Queue{
	int arr[N];
	int count;
	int p_out;
	int p_inp;
}queue;

queue init();
int push(queue *q, int element);
int pop(queue *q);
void printq(queue *q);


int main(){
	queue q = init();
	push(&q, 1);
	push(&q, 2);
	push(&q, 3);
	push(&q, 4);
	pop(&q);

	printq(&q);

	push(&q, 5);
	push(&q, 6);

	printq(&q);

	pop(&q);
	pop(&q);
	pop(&q);
	pop(&q);
	printq(&q);
	//pop(&q);
	//pop(&q);

	push(&q, 7);
	push(&q, 8);
	push(&q, 9);
	push(&q, 10);

	printq(&q);
	return 0;
}


queue init(){
	queue out = {{0}, 0, N, 0};
	return out;
}

int push(queue *q, int element){
	if (q->p_inp == N && q->p_out != 0)
		q->p_inp = 0;
	if (q->p_inp == N || q->p_inp == q->p_out) return 1;
	q->arr[q->p_inp] = element;
	(q->count) ++;
	(q->p_inp) ++;
	return 0;
}

int pop(queue *q){
	if (q->p_out == N && q->p_inp != 0)
		q->p_out = 0;
	//if (q->p_out == N || q->p_out == q->p_inp) return 0;
	int out = q->arr[q->p_out];
	q->arr[q->p_out] = 0;
	(q->count) --;
	(q->p_out) ++;
	return out;
}

void printq(queue *q){
	for (int i = 0; i < N; i++)
		printf("%d ", (q->arr)[i]);
	printf("\n");
}
