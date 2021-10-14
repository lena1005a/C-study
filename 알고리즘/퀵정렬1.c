#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int start, end;
}NODE;

NODE partition(int a[], int start, int end, int pivInd);
void quickSort(int a[], int start, int end);
int findPivotIndex(int a[], int start, int end);
void swap(int a[], int index1, int index2);

int main() {
	int *l, n;
	scanf("%d", &n);
	l = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++)
		scanf("%d", &l[i]);
	quickSort(l, 0, n - 1);
	for (int i = 0; i < n; i++)
		printf(" %d", l[i]);

	free(l);
}

void quickSort(int a[], int start, int end) {
	if (start < end) {
		NODE pivInd = partition(a, start, end, findPivotIndex(a, start, end));
		quickSort(a, start, pivInd.start - 1);
		quickSort(a, pivInd.end + 1, end);
	}
}

NODE partition(int a[], int start, int end, int pivInd) {
	int sPivot, left, right, tmp;
	NODE dPivot;

	sPivot = a[pivInd];
	swap(a, pivInd, end);

	left = start;
	right = end - 1;

	while (left <= right) {
		while (left <= right && a[left] <= sPivot) {
			left++;
		}
		while (left <= right && a[right] >= sPivot) {
			right--;
		}
		if (left < right) {
			swap(a, left, right);
		}
	}
	swap(a, left, end);

	dPivot.start = left;
	dPivot.end = left;
	return dPivot;

	/*
	while (left < right) {
		while (left < pivInd) {
			if (a[left] > sPivot) {
				swap(a, left, pivInd);
				pivInd = left;
				break;
			}
			left++;
		}
		while (pivInd < right) {
			if (sPivot >= a[right]) {
				swap(a, pivInd, right);
				pivInd = right;
				break;
			}
			right--;
		}
	}

	//오름차순
	dPivot.end = pivInd;
	left = start;
	while (left < right) {
		while (left < pivInd) {
			if (a[left] >= sPivot) {
				swap(a, left, pivInd);
				pivInd = left;
				break;
			}
			left++;
		}
		while (pivInd < right) {
			if (sPivot > a[right]) {
				swap(a, pivInd, right);
				pivInd = right;
				break;
			}
			right--;
		}
	}
	dPivot.start = pivInd;
	return dPivot;
	*/
}



int findPivotIndex(int a[], int start, int end) { //랜덤 중 잴 큰 수 반환
	int ind[3];
	srand(time(NULL));

	/*
	while (1) {
		for (int i = 0; i < 3; i++)
			ind[i] = start + (rand() % (end - start + 1));
		if (ind[0] != ind[1] && ind[0] != ind[2] && ind[1] != ind[2])
			break;
	}
	/*
	if (a[ind[0]] > a[ind[1]] && a[ind[0]] > a[ind[2]]) {
		if (a[ind[1]] > a[ind[2]])
			return ind[1];
		else
			return ind[2];
	}
	else if (a[ind[1]] > a[ind[0]] && a[ind[1]] > a[ind[2]]) {
		if (a[ind[0]] > a[ind[2]])
			return ind[0];
		else
			return ind[2];
	}
	else {
		if (a[ind[0]] > a[ind[1]])
			return ind[0];
		else
			return ind[1];
	}*/

	ind[0] = start + (rand() % (end - start + 1));
	return ind[0];
}

void swap(int a[], int index1, int index2) {
	int tmp = a[index1];
	a[index1] = a[index2];
	a[index2] = tmp;
}