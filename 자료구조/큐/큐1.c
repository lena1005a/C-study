#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int enqueue(int *q, int *f, int *r, int q_cnt, int data);
int dequeue(int *q, int *f, int *r, int q_cnt);
void print(int *q, int q_cnt);

int main() {
	int *q, q_cnt, n, data, f = 0, r = 0;
	char op_type;

	scanf("%d %d", &q_cnt, &n);
	q = (int *)malloc(sizeof(int)*q_cnt);
	for (int i = 0; i < q_cnt; i++) {
		*(q + i) = 0;
	}

	for (int i = 0; i < n; i++) {
		getchar();
		scanf("%c", &op_type);
		if (op_type == 'I') {
			getchar();
			scanf("%d", &data);
			if (!enqueue(q, &f, &r, q_cnt, data)) {
				printf("overflow");
				print(q, q_cnt);
				return 0;
			}
		}
		else if (op_type == 'D') {
			if (!dequeue(q, &f, &r, q_cnt)) {
				printf("underflow");
				return 0;
			}
		}
		else {//P»èÁ¦
			print(q, q_cnt);
		}
	}
}


int enqueue(int *q, int *f, int *r, int q_cnt, int data) {
	*r += 1;
	*r %= q_cnt;
	if (*f == *r) return 0;
	*(q + *r) = data;
	return 1;
}

int dequeue(int *q, int *f, int *r, int q_cnt) {
	if (*f == *r) return 0;
	*f += 1;
	*f %= q_cnt;
	*(q + *f) = 0;
	return 1;
}

void print(int *q, int q_cnt) {
	for (int *p = q; p < q + q_cnt; p++) {
		printf(" %d", *p);
	}printf("\n");
}