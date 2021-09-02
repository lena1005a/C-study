#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct st_list {
	char data;
	struct st_list *next, *prev;
}Stack;

Stack *init_Node() {
	Stack *new = (Stack *)malloc(sizeof(Stack));
	new->next = NULL;
	new->prev = NULL;
	return new;
}

void PM_convert(char *arr);
void result(char *arr);
void push_st(Stack *head, char data);
char pop_st(Stack *tail);
char peek_st(Stack *tail);
int priority(char data);

int main() {
	int N;
	char arr[101];
	scanf("%d", &N);
	getchar();
	for (int i = 0; i < N; i++) {
		gets(arr);
		PM_convert(arr);
		result(arr);
	}
}


void PM_convert(char *arr) {
	char *p, *q;
	for (p = arr; *p; p++) {
		if (p == arr) {
			if (*p == '-') *p = 'm';
			if (*p == '+') *p = 'p';
		}
		else {
			if (*p == '&' || *p == '|') {
				for (q = p + 1; *q; q++) {
					*(q - 1) = *q;
				}
				*(q - 1) = 0;
			}
		}
	}

	for (p = arr + 1; *p; p++) {
		if ((*(p - 1) < 'A' || *(p - 1) > 'Z') && *(p - 1) != ')') {
			if (*p == '-') *p = 'm';
			if (*p == '+') *p = 'p';
		}
	}
}

void result(char *arr) {
	char *p, tmp;
	Stack *Head, *Tail;
	Head = init_Node();
	Tail = init_Node();
	Head->next = Tail;
	Tail->prev = Head;


	for (p = arr; *p; p++) {
		if ('A' <= *p && *p <= 'Z') printf("%c", *p);
		else if (*p == '(') push_st(Head, *p);
		else if (*p == ')') {
			while (peek_st(Tail) != '(') { // 스택맨위 데이터가 '('가 나올때까지 반복 
				tmp = pop_st(Tail);
				if (tmp == '|' || tmp == '&') printf("%c%c", tmp, tmp);
				else if (tmp == 'm') printf("-");
				else if (tmp == 'p') printf("+");
				else printf("%c", tmp);
			}
			tmp = pop_st(Tail);
		}
		else {
			while ((Head->next != Tail) && priority(*p) <= priority(peek_st(Tail))) {
				tmp = pop_st(Tail);
				if (tmp == '|' || tmp == '&') printf("%c%c", tmp, tmp);
				else if (tmp == 'm') printf("-");
				else if (tmp == 'p') printf("+");
				else printf("%c", tmp);
			}
			push_st(Head, *p);
		}
	}

	while (Head->next != Tail) {
		tmp = pop_st(Tail);
		if (tmp == '|' || tmp == '&') printf("%c%c", tmp, tmp);
		else if (tmp == 'm') printf("-");
		else if (tmp == 'p') printf("+");
		else printf("%c", tmp);
	}
	printf("\n");
}


void push_st(Stack *head, char data) {
	Stack *cur = head;  //HT
	

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
char peek_st(Stack *tail) {
	return tail->prev->data;
}


int priority(char data) {
	if (data == '!' || data == 'p' || data == 'm') {
		return 6;
	}
	if (data == '*' || data == '/') {
		return 5;
	}
	if (data == '+' || data == '-') {
		return 4;
	}
	if (data == '>' || data == '<') {
		return 3;
	}
	if (data == '&') {
		return 2;
	}
	if (data == '|') {
		return 1;
	}
	return 0;
}