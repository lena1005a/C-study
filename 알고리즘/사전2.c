#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int binSearch(int a[], int key, int size);

int main() {
	int *arr, n, key;
	scanf("%d %d", &n, &key);
	arr = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	printf(" %d", binSearch(arr, key, n));
	free(arr);
}

int binSearch(int a[], int key, int size) {
	int left = 0, right = size - 1, mid;

	while (1) {
		mid = (left + right) / 2;
		if (key > a[right]) return size;
		else if (key <= a[left]) return left;
		else if (key > a[mid]) left = mid + 1;
		else if (key <= a[mid - 1]) right = mid - 1;
		else return mid;
	}
}