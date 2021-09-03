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

	for (int i = 1; i < N; i++) { //i=6
		index = i;
		for (int j = i - 1; j >= 0; j--) {
			if (n[i] < n[j]) index = j;
		}
		tmp = n[i];
		for (int k = i; k > index; k--) {
			n[k] = n[k-1];
		}
		n[index] = tmp;

	}

	for (int i = 0; i < N; i++) {
		printf(" %d", n[i]);
	}
}