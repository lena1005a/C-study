#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct b_tree {
	int data;
	struct b_tree *left, *right;
}B_Node;


B_Node *child_Node_Create(int data) {
	B_Node *new = (B_Node *)malloc(sizeof(B_Node));
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	return new;
}

B_Node *root_Node_Create(int data, B_Node *l, B_Node *r) {
	B_Node *new = (B_Node *)malloc(sizeof(B_Node));
	new->data = data;
	new->left = l;
	new->right = r;

	return new;
}

void search_Node(B_Node **root,int n);

int main() {
	B_Node *t[9] = { 0 };

	t[4] = child_Node_Create(70);
	t[5] = child_Node_Create(90);
	t[2] = root_Node_Create(30, t[4], t[5]);

	t[7] = child_Node_Create(130);
	t[8] = child_Node_Create(80);
	t[6] = root_Node_Create(120, t[7], t[8]);

	t[3] = root_Node_Create(50, 0, t[6]);

	t[1] = root_Node_Create(20, t[2], t[3]);

	int n;
	scanf("%d", &n);
	if (1 <= n && n <= 8) {
		search_Node(t, n);
	}
	else {
		printf("-1");
	}
}

void search_Node(B_Node **root, int n) {
	B_Node *tmp = root[n];
	printf("%d ", tmp->data);

	if (tmp->left) {
		printf("%d ", (tmp->left)->data);
	}
	if (tmp->right) {
		printf("%d ", (tmp->right)->data);
	}
}