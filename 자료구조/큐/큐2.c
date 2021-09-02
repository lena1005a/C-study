#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct link_list {
	int data;
	struct link_list *next, *prev;
}Dq;

void add_front(Dq **f, Dq **r, int data);
void add_rear(Dq **f, Dq **r, int data);
int delete_front(Dq **f, Dq **r);
int delete_rear(Dq **f, Dq **r);
void print(Dq *f);


int main() { //AF AR DF DR P
	Dq *f, *r;
	f = (Dq *)malloc(sizeof(Dq));
	r = (Dq *)malloc(sizeof(Dq));
	f = 0, r = 0;

	int op_cnt, data;
	char op_type;
	scanf("%d", &op_cnt);
	for (int i = 0; i < op_cnt; i++) {
		getchar();
		scanf("%c", &op_type);
		if (op_type == 'A') {
			scanf("%c %d", &op_type, &data);
			if (op_type == 'F') {
				add_front(&f, &r, data);
			}
			else {
				add_rear(&f, &r, data);
			}
		}
		else if (op_type == 'D') {
			scanf("%c", &op_type);
			if (op_type == 'F') {
				if (!delete_front(&f, &r)) break;
			}
			else {
				if (!delete_rear(&f, &r)) break;
			}
		}
		else { // ÇÁ¸°Æ®
			print(f);
		}
	}
}


void add_front(Dq **f, Dq **r, int data) {
	Dq *new = (Dq *)malloc(sizeof(Dq));
	new->data = data;
	new->next = *f;
	new->prev = 0;
	if (*f == 0) {
		*f = new;
		*r = new;
	}
	else {
		(*f)->prev = new;
		*f = new;
	}
}

void add_rear(Dq **f, Dq **r, int data) {
	Dq *new;
	new = (Dq *)malloc(sizeof(Dq));
	new->data = data;
	new->next = 0;
	new->prev = *r;
	if (*r == 0) {
		*f = new;
		*r = new;
	}
	else {
		(*r)->next = new;
		*r = new;
	}
}

int delete_front(Dq **f, Dq **r) {
	Dq *p;
	if (*f == 0) {
		printf("underflow\n");
		return 0;
	}
	p = (*f)->next;
	if (p != 0) p->prev = 0;
	else *r = p;

	free(*f);
	*f = p;
}

int delete_rear(Dq **f, Dq **r) {
	Dq *p;
	if (*r == 0) {
		printf("underflow\n");
		return 0;
	}
	p = (*r)->prev;
	if (p != 0) p->next = 0;
	else *f = p;

	free(*r);
	*r = p;
}

void print(Dq *f) {
	for (Dq *p = f; p; p = p->next) {
		printf(" %d", p->data);
	}printf("\n");
}