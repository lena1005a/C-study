#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//합집합과 교집합 출력

typedef struct SET {
	int data;
	struct SET *next;
}Set;

Set *init_Node() {
	Set *new = (Set *)malloc(sizeof(Set));
	new->next = NULL;
}

void add_Node(Set *head, int data);
Set *union_set(Set *A, Set *B);
Set *intersect_set(Set *A, Set *B);
void print_set(Set *head);
int member_data(Set *head, int data);


int main() {
	Set *A, *B, *u, *i;
	A = init_Node();
	B = init_Node();


	int size, num;
	scanf("%d", &size);
	for (int i = 0; i < size; i++) {
		scanf("%d", &num);
		add_Node(A, num);
	}

	scanf("%d", &size);
	for (int i = 0; i < size; i++) {
		scanf("%d", &num);
		add_Node(B, num);
	}

	u = union_set(A, B);
	print_set(u);
	printf("\n");
	i = intersect_set(A, B);
	print_set(i);

}

void add_Node(Set *head, int data) {
	Set *cur = head;

	for (int i = 0; ; i++) {
		if (cur->next == NULL) break;
		cur = cur->next;
	}

	Set *new = (Set *)malloc(sizeof(Set));
	new->data = data;
	cur->next = new;
	new->next = NULL;
}

void print_set(Set *head) {
	Set *cur = head;

	for (int i = 0; ; i++) {
		cur = cur->next;
		if (cur == NULL) {
			if (i == 0) printf(" 0"); return;
			return;
		}
		printf(" %d", cur->data);
	}
}


//오름차순 입력만 존재
Set *union_set(Set *A, Set *B) {
	Set *head = init_Node();
	Set *a = A, *b = B;
	a = a->next;
	b = b->next;

	while (a&&b) {
		if (a->data < b->data) {
			add_Node(head, a->data);
			a = a->next;
		}
		else if (a->data > b->data) {
			add_Node(head, b->data);
			b = b->next;
		}
		else {
			add_Node(head, a->data);
			a = a->next;
			b = b->next;
		}
	}
	while (a) {
		add_Node(head, a->data);
		a = a->next;
	}
	while (b) {
		add_Node(head, b->data);
		b = b->next;
	}

	return head;
}

Set *intersect_set(Set *A, Set *B) {
	Set *head = init_Node();
	Set *a = A, *b = B;

	while (a) {
		a = a->next;
		if (a == NULL) {
			return head;
		}
		if (member_data(B, a->data)) {
			add_Node(head, a->data);
		}
	}
	
}

int member_data(Set *head, int data) {
	//멤버면 1반환 아니면 0반환
	Set *cur = head;

	for (int i = 0; ; i++) {
		cur = cur->next;
		if (cur == NULL) {
			return 0;
		}
		if (cur->data == data) {
			return 1;
		}
	}
	return 0;
}