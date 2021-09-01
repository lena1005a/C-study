#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct SET {
	int data;
	struct SET *next;
}Set;

Set *init_Node() {
	Set *new = (Set *)malloc(sizeof(Set));
	new->next = NULL;
	new->data = 0;
	return new;
}

void add_Node(Set *head, int num);
int subset(Set *A, Set *B);
int member(Set *B, int data);

int main() {

	Set *A, *B;
	A = init_Node();
	B = init_Node();


	int size, num;
	scanf("%d", &size);
	for (int i = 0; i < size; i++) {
		scanf("%d", &num);
		if (i == 0) {
			A->data = num;
			continue;
		}
		else add_Node(A, num);
	}

	scanf("%d", &size);
	for (int i = 0; i < size; i++) {
		scanf("%d", &num);
		if (i == 0) {
			B->data = num;
			continue;
		}
		else add_Node(B, num);
	}

	printf("%d", subset(A, B));
}

void add_Node(Set *head, int num) {
	Set *cur = head;
	for (; cur->next; cur = cur->next);

	Set *new = (Set *)malloc(sizeof(Set));
	new->data = num;
	cur->next = new;
	new->next = NULL;
}

int subset(Set *A, Set *B) { //B가 A를 포함하면 0, 아니면 B에 안속한 잴작은 수
	if (A->data == 0) {
		return 0;
	}

	while (1) {
		// 현 A데이터가 B에 속하냐
		if (member(B, A->data)) A= A->next;
		else return A->data;

		if (!A) return 0;
	}

}

int member(Set *B, int data) {
	Set *cur = B;

	for (; cur; cur = cur->next) {
		if (cur->data == data) {
			return 1; 
		}
	}

	return 0;
}