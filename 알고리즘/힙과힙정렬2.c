#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//배열(순차힙):연결트리(연결힙)
// 삽입식=제자리 : 상향식

//문제조건= 최대힙+상향식+배열0번자리 비움+재귀&비재귀
int n = 0;
int H[99];

void rBuildHeap(int i); //재귀
void buildHeap(); //비재귀
void downHeap(int i);
void printHeap();
void swap(int n1, int n2);

int main() {
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