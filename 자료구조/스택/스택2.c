#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char st[1001];
void push_st(char *st, int *top, char data);
char pop_st(char *st, int *top);


int main() {
	char arr[1001], comp;
	gets(arr);

	int cnt_arr, re_cnt = 0, top = -1, result = 1;//result: 0실패/ 1성공

	cnt_arr = strlen(arr);
	for (int i = 0; i < cnt_arr; i++) {
		if (arr[i] == '{' || arr[i] == '[' || arr[i] == '(') {
			re_cnt++;
			push_st(st, &top, arr[i]);
		}
		else if (arr[i] == '}' || arr[i] == ']' || arr[i] == ')') {
			re_cnt++;
			comp = pop_st(st, &top);
			if (arr[i] == '}') {
				if (comp != '{') result = 0;
			}
			else if (arr[i] == ']') {
				if (comp != '[') result = 0;
			}
			else {
				if (comp != '(') result = 0;
			}
		}
	}

	if (top != -1) result = 0;
	if (result == 0) printf("Wrong_%d", re_cnt);
	else printf("OK_%d", re_cnt);
}

void push_st(char *st, int *top, char data) {
	*top += 1;
	st[*top] = data;
}

char pop_st(char *st, int *top) {
	char re_data = st[*top];
	*top -= 1;
	return re_data;
}
