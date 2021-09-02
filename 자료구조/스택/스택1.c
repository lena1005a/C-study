#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void push_stack(char *st, int *t, char data);
char pop_stack(char *st, int *t);
char peek_stack(char *st, int *t);
void print_stack(char *st, int *t);

int main() {
	int N, op_cnt, top = -1, n;
	char arr[10], data, *st;

	scanf("%d %d", &N, &op_cnt);
	getchar();

	st = (char *)malloc(sizeof(char)*(N+1));
	for (int i = 0; i < op_cnt; i++) {
		scanf("%s", arr);

		if (0==strcmp(arr, "PUSH")) {
			getchar();
			scanf("%c", &data);
			if (top == N - 1) printf("Stack FULL\n");
			else push_stack(st, &top, data);
		}
		else if (0==strcmp(arr, "POP")) {
			if (top == -1) printf("Stack Empty\n");
			else data = pop_stack(st, &top);
		}
		else if (0==strcmp(arr, "PEEK")) {
			if (top == -1) printf("Stack Empty\n");
			else printf("%c\n", pop_stack(st, &top));
		}
		else if (0==strcmp(arr, "DUP")) {
			if (top == -1) {
				printf("Stack Empty\n");
				continue;
			}
			else if (top == N - 1) {
				printf("Stack FULL\n");
				continue;
			}
			else {
				data = pop_stack(st, &top);
				push_stack(st, &top, data);
				push_stack(st, &top, data);
			}
		}
		else if (0==strcmp(arr, "PRINT")) {
			print_stack(st, &top);
		}
		else if (0==strcmp(arr, "UpR")) { //스택 맨위 n개 데이터 회전(3: rats ->atrs)
			scanf("%d", &n);
			if (n > top + 1) continue;
			data = pop_stack(st, &top);
			char *tmp = (char *)malloc(sizeof(char)*(n));
			for (int j = 0; j < n - 1; j++) {
				tmp[j] = pop_stack(st, &top);
			}
			push_stack(st, &top, data);
			for (int j = n-2; j >=0; j--) { //n=3 
				push_stack(st, &top, tmp[j]);
			}
			free(tmp);
		}
		else { //DownR 스택 맨위 n개 데이터 회전(4: stars ->rstas)
			scanf("%d", &n);
			if (n > top + 1) continue;
			char *tmp = (char *)malloc(sizeof(char)*(n));
			for (int j = 0; j < n - 1; j++) {
				tmp[j] = pop_stack(st, &top);
			}
			data = pop_stack(st, &top);
			for (int j = n - 2; j >= 0; j--) { //n=3 
				push_stack(st, &top, tmp[j]);
			}
			push_stack(st, &top, data);
			free(tmp);
		}
	}
}


void push_stack(char *st, int *t, char data) {
	*t += 1;
	st[*t] = data;
}

char pop_stack(char *st, int *t) {
	char data = st[*t];
	*t -= 1;
	return data;
}

char peek_stack(char *st, int *t) {
	char data = st[*t];
	return data;
}

void print_stack(char *st, int *t) {

	for (int i = *t; i >= 0; i--) {
		printf("%c", st[i]);
	}printf("\n");
}