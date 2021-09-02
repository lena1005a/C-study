#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct st {
	char data;
	struct st *next, *prev;
}Stack;

Stack *init_Node() {
	Stack *new = (Stack *)malloc(sizeof(Stack));
	new->next = NULL;
	new->prev = NULL;
	return new;
}

void calculate(char *arr);
void push_st(Stack *head, char data);
char pop_st(Stack *tail);

int main() {
	int N;
	char arr[101];

	scanf("%d", &N);
	getchar();
	for (int i = 0; i < N; i++) {
		gets(arr);
		calculate(arr);
	}
}

void calculate(char *arr) {
	Stack *Head, *Tail;
	Head = init_Node();
	Tail = init_Node();
	Head->next = Tail;
	Tail->prev = Head;

	char *p, a, b;

	for (p = arr; *p; p++) {
		if ('0' <= *p && *p <= '9') push_st(Head, *p);
		else {
			a = pop_st(Tail);
			a = a - '0';
			b = pop_st(Tail);
			b = b - '0';

			if (*p == '+') push_st(Head, ((b + a) + '0'));
			if (*p == '-') push_st(Head, ((b - a) + '0'));
			if (*p == '*') push_st(Head, ((b * a) + '0'));
			if (*p == '/') push_st(Head, ((b / a) + '0'));
		}
	}
	printf("%d\n", pop_st(Tail) - '0');
}

void push_st(Stack *head, char data) {
	Stack *cur = head;  
	for (; cur->next; cur = cur->next);

	Stack *new = (Stack *)malloc(sizeof(Stack));
	new->data = data;
	new->next = cur;
	cur->prev->next = new;
	new->prev = cur->prev;
	cur->prev = new;
}

char pop_st(Stack *tail) {
	Stack *cur = tail;

	cur = cur->prev;
	char data = cur->data;
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;

	free(cur);
	return data;
}