#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int binSearch(int a[], int key, int left, int right);

int main() {
	int *arr, n, key;
	scanf("%d %d", &n, &key);
	arr = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	printf("%d", binSearch(arr, key, 0, n - 1));
	free(arr);
}

int binSearch(int a[], int key, int left, int right) {
	int mid = (left + right) / 2;

	if (key < a[left]) return -1;
	else if (key >= a[right]) return right;
	else if (key < a[mid])return binSearch(a, key, left, mid - 1);
	else if (key >= a[mid + 1])return binSearch(a, key, mid + 1, right);
	else return mid;

}#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int binSearch(int a[], int key, int left, int right);

int main() {
	int *arr, n, key;
	scanf("%d %d", &n, &key);
	arr = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	printf("%d", binSearch(arr, key, 0, n - 1));
	free(arr);
}

int binSearch(int a[], int key, int left, int right) {
	int mid = (left + right) / 2;

	if (key < a[left]) return -1;
	else if (key >= a[right]) return right;
	else if (key < a[mid])return binSearch(a, key, left, mid - 1);
	else if (key >= a[mid + 1])return binSearch(a, key, mid + 1, right);
	else return mid;

}