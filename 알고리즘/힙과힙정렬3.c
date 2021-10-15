#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int n = 0;
int H[99];

void rBuildHeap(int i); //재귀
void buildHeap(); //비재귀
void downHeap(int i);
void swap(int n1, int n2);
void inPlaceHeapSort();
void printArray();

int main() {
	int key_cnt, key;

	scanf("%d", &key_cnt);

	for (int i = 0; i < key_cnt; i++) {
		scanf("%d", &key);
		H[++n] = key;
	}

	rBuildHeap(1);
	inPlaceHeapSort();
	printArray();
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
	/*
	기존 배열의 힙생성과는 다름
	if (H[child] < H[i] && H[child + 1] < H[i]) return;

	if (H[child] < H[child + 1]) {
		child += 1;
	}*/

	if (child < n && H[child] < H[child + 1]) {
		child += 1;
	}
	if (H[child] > H[i]) swap(i, child);

	downHeap(child);
}

void inPlaceHeapSort() { //제자리 힙정렬
	int tmp, nn;
	nn = n;
	for (int i = n; i >= 1; i--) {
		swap(i, 1);
		n--;
		downHeap(1);
	}
	n = nn;
}

void swap(int n1, int n2) {
	int tmp = H[n1];
	H[n1] = H[n2];
	H[n2] = tmp;
}

void printArray() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
}