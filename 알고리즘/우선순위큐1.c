#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int *n, N, tmp, index;
	scanf("%d", &N);
	n = (int *)malloc(sizeof(int)*N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &n[i]);
	}

	for (int i = N - 1; i >= 1; i--) {
		index = i;
		for (int j = i - 1; j >= 0; j--) {
			if (n[index] < n[j]) index = j;
		}
		tmp = n[index];
		n[index] = n[i];
		n[i] = tmp;
	}

	for (int i = 0; i < N; i++) {
		printf(" %d", n[i]);
	}

}