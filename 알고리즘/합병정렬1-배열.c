#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void mergeSort(int a[], int n);
void rmergeSort(int a[], int l, int r);
void merge(int a[], int l, int r, int m);

int main() {
	int n;
	scanf("%d", &n);
	int *arr = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	mergeSort(arr, n);
	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

}

void mergeSort(int a[], int n) {
	rmergeSort(a, 0, n - 1);
}
void rmergeSort(int a[], int l, int r) {
	int m;

	if (l < r) {
		int m = (l + r) / 2;
		rmergeSort(a, l, m);
		rmergeSort(a, m + 1, r);
		merge(a, l, r, m);
	}
}
void merge(int a[], int l, int r, int m) {
	int i = l, j = m + 1, k = l;
	int *b = (int *)malloc(sizeof(int)*(r + 1));
	while (i <= m && j <= r) {
		if (a[i] <= a[j]) {
			b[k++] = a[i++];
		}
		else {
			b[k++] = a[j++];
		}
	}

	while (i <= m) {
		b[k++] = a[i++];
	}
	while (j <= r) {
		b[k++] = a[j++];
	}
	for (k = l; k <= r; k++) {
		a[k] = b[k];
	}
	free(b);
}