#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int n;
	struct Node *next;
}node;

node* reverse(node* head){
	node* tmp = head;
	node* tmpPrev = NULL;
	node* tmpNext;
	while (tmp->next){
		tmpNext = tmp->next;
		tmp->next = tmpPrev;
		tmpPrev = tmp;
		tmp = tmpNext;
	}
	tmp->next = tmpPrev;
	return tmp;
}

void print(node* head){
	node* tmp = head;
	while (tmp->next != NULL){
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
	printf("%d\n", tmp->n);
}



int main(){
	node* p1 = (node*)malloc(sizeof(node));
	node* p2 = (node*)malloc(sizeof(node));
	node* p3 = (node*)malloc(sizeof(node));
	node* p4 = (node*)malloc(sizeof(node));
	node* p5 = (node*)malloc(sizeof(node));

	p1->n = 5; p1->next = p2;
	p2->n = 7; p2->next = p3;
	p3->n = 2; p3->next = p4;
	p4->n = 6; p4->next = p5;
	p5->n = 9; p5->next = NULL;

	print(p1);
	printf("____________________________________\n");
	node* newp = reverse(p1);
	print(newp);

	free(p1);
	free(p2);
	free(p3);
	free(p4);
	free(p5);
}
