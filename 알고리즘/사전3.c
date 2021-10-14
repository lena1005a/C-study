#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int binSearch(int n, int a, int b);

int main() {
	int a, b, n;
	scanf("%d %d %d", &a, &b, &n);
	printf("%d", binSearch(n, a, b));
}

int binSearch(int n, int a, int b) {
	int mid = (a + b) / 2;
	char input;
	if (n == 0) return mid;
	scanf(" %c", &input);
	if (input == 'Y') return binSearch(n - 1, mid + 1, b);
	else return binSearch(n - 1, a, mid);
}