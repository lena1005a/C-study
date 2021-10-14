#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int data;
	struct node *next;
}NODE;

NODE *init(int n);
NODE *mergeSort(NODE *std, int size);
NODE *partition(NODE *std, int k);
NODE *merge(NODE *p1, NODE *p2);

int main() {
	int n;
	scanf("%d", &n);

	NODE *list = init(n);
	list = mergeSort(list, n);
	for (NODE *cur = list; cur; cur = cur->next) {
		printf(" %d", cur->data);
	}

}

NODE *init(int n) {
	NODE *new = (NODE *)malloc(sizeof(NODE));
	scanf("%d", &new->data);
	if (n == 1) new->next = NULL;
	else new->next = init(n - 1);
	return new;
}

NODE *mergeSort(NODE *std, int size) {
	if (size <= 1) return std;
	int m = size / 2;
	NODE *p1, *p2;
	p1 = std;
	p2 = partition(std, m);
	p1 = mergeSort(p1, m);
	p2 = mergeSort(p2, size - m);
	return merge(p1, p2);
}

NODE *partition(NODE *std, int k) {
	NODE *p2 = std, *tmp = std;
	while (k--) {
		p2 = p2->next;
		if (k == 1) tmp = p2;
	}
	tmp->next = NULL;
	return p2;
}

NODE *merge(NODE *p1, NODE *p2) {
	NODE *tmp, *tmp2;
	tmp2 = (NODE *)malloc(sizeof(NODE));
	tmp = tmp2;

	for (NODE *left = p1, *right = p2; left != NULL || right != NULL; tmp = tmp->next) {
		if (right == NULL || (left != NULL && left->data < right->data)) {
			tmp->next = left;
			left = left->next;
		}
		else {
			tmp->next = right;
			right = right->next;
		}
	}
	tmp = tmp2->next;
	free(tmp2);
	return tmp;
}