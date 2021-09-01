#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ListNode {
	char data;
	struct ListNode *prev, *next;
}Node;

void add_Node(Node list, int r, char e);
void delete_Node(Node list, int r);
void get(Node list, int r);
void print(Node list);

int main() {
	Node Head, Tail;
	Head.next = &Tail;
	Tail.prev = &Head;
	Head.prev = NULL;
	Tail.next = NULL;

	char op, e;
	int op_cnt, r;
	scanf("%d", &op_cnt);
	getchar();

	for (int i = 0; i < op_cnt; i++) {
		scanf("%c", &op);

		if (op == 'P') {
			print(Head);
		}
		else {
			if (op == 'G' || op == 'D') {
				scanf("%d", &r);
				if (op == 'G') {
					get(Head, r);
				}
				else {
					delete_Node(Head, r);
				}

			}
			else { //AÀÎ°æ¿ì
				scanf("%d %c", &r, &e);
				add_Node(Head, r, e);
			}
		}
		getchar();
	}

}

void add_Node(Node list, int r, char e) {
	Node *new = (Node *)malloc(sizeof(Node));
	new->data = e;

	if (r <= 0) {
		printf("invalid position\n");
		return;
	}

	Node *tmp = &list;   // H:  :T
	for (int i = 0; i < r; i++) { 
		if (tmp->next == NULL) {
			printf("invalid position\n");
			return;
		}
		tmp = tmp->next;
	}

	new->next = tmp;
	tmp->prev->next = new;
	new->prev = tmp->prev;
	tmp->prev = new;
}

void delete_Node(Node list, int r) {
	Node *tmp = &list;

	if (r <= 0) {
		printf("invalid position\n");
		return;
	}
	for (int i = 0; i < r; i++) {
		if (tmp->next == NULL) {
			printf("invalid position\n");
			return;
		}
		tmp = tmp->next;
	}   // HaT
	


	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;

	free(tmp);
}

void get(Node list, int r) {
	Node *tmp = &list;

	// HST   //0 1 2 
	if (r <= 0) {
		printf("invalid position\n");
		return;
	}
	for (int i = 0; i < r; i++) {
		if (tmp->next == NULL) {
			printf("invalid position\n");
			return;
		}
		tmp = tmp->next;
	}

	if (tmp->next == NULL) {
		printf("invalid position\n");
		return;
	}

	printf("%c", tmp->data);
}

void print(Node list) {
	Node *tmp = &list;

	tmp = tmp->next;
	for ( ;tmp->next;tmp=tmp->next ) {
		if (tmp == NULL) {
			break;
		}
		printf("%c", tmp->data);
	}
	printf("\n");
}

