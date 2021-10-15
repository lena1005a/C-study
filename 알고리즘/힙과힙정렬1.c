#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//배열(순차힙):연결트리(연결힙)
// 삽입식=제자리 : 상향식

//문제조건= 최대힙+삽입식+배열0번자리 비움
int n = 0;
int H[99];

void insertitem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();
void swap(int n1, int n2);

int main() {
	char op_type;
	int key;

	while (1) {
		scanf("%c", &op_type);
		if (op_type == 'i') {
			scanf("%d", &key);
			if (n >= 99) continue;
			insertitem(key);
			printf("0\n");
		}
		else if (op_type == 'd') printf("%d\n", removeMax());
		else if (op_type == 'p') {
			if (n < 1) {
				getchar();
				continue;
			}
			printHeap();
		}
		else return;
		getchar();
	}
}

void insertitem(int key) {
	n += 1;
	H[n] = key;
	upHeap(n);
}

int removeMax() {
	if (n == 0) return 0;

	int key = H[1];
	H[1] = H[n];
	H[n] = 0;
	n -= 1;
	downHeap(1);
	return key;
}

void upHeap(int i) {
	if (i == 1 || (H[i] <= H[i / 2])) return;
	swap(i, i / 2);
	upHeap(i / 2);
}

void downHeap(int i) {
	int child = 2 * i;

	if (child > n) return;
	if (H[child] < H[i] && H[child + 1] < H[i]) return;

	if (H[child] <= H[child + 1]) {
		child = child + 1;
	}
	swap(i, child);
	downHeap(child);
}

void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}printf("\n");
}

void swap(int n1, int n2) {
	int tmp = H[n1];
	H[n1] = H[n2];
	H[n2] = tmp;
}