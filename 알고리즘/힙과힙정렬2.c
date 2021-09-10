#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void rBuildHeap(int i); //¿Á±Õ
void buildHeap(); //∫Ò¿Á±Õ
void downHeap(int i);
void printHeap();

int H[99] = { 0 };
int n = 0;

void main() {
	int key_cnt, key;

	scanf("%d", &key_cnt);

	for (int i = 0; i < key_cnt; i++) {
		scanf("%d", &key);
		n += 1;
		H[n] = key;
	}

	buildHeap(1);
	printHeap();
}

void rBuildHeap(int i) {
	if (i > n) return;

	rBuildHeap(2 * i);
	rBuildHeap((2 * i) + 1);
	downHeap(i);
	return;
}

void buildHeap() {
	for (int i = n / 2; i >= 1; i--) {
		downHeap(i);
	}

	return;
}


void downHeap(int i) {
	if (2 * i > n) return;
	if (H[2 * i] < H[i] && H[2 * i + 1] < H[i]) return;

	int small = (2 * i), tmp;
	if (H[2 * i] <= H[(2 * i) + 1]) {
		small = (2 * i) + 1;
	}
	tmp = H[small];
	H[small] = H[i];
	H[i] = tmp;

	downHeap(small);
}

void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
}