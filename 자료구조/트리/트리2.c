#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct b_tree {
	int id, data;
	struct b_tree *left, *right;
}B_Node;


B_Node *Create_Node(int id, int data) {
	B_Node *new = (B_Node *)malloc(sizeof(B_Node));
	new->id = id;
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	return new;
}

void Connect_Node(B_Node *p, B_Node *l, B_Node *r);
void inorder(B_Node *root);
void preorder(B_Node *root);
void postorder(B_Node *root);
void find_Node(B_Node *root, int type, int id);

int main() {
	B_Node root;
	int a, b;
	
	scanf("%d %d", &a, &b); //순회방식, 노드id
	
	root.id = 1;
	root.data = 20;

	B_Node *l = Create_Node(2, 30);
	B_Node *r = Create_Node(3, 50);
	Connect_Node(&root, l, r);

	l = Create_Node(4, 70);
	r = Create_Node(5, 90);
	Connect_Node(root.left, l, r);

	l = 0;
	r = Create_Node(6, 120);
	Connect_Node(root.right, l, r);

	l = Create_Node(7, 130);
	r = Create_Node(8, 80);
	Connect_Node(root.right->right, l, r);

	if (8 <= b || b <= 0 || a <= 0 || a >= 4) {
		printf("-1");
		return 0;
	}

	else {
		find_Node(&root, a, b);
	}
}

void Connect_Node(B_Node *p, B_Node *l, B_Node *r) {
	p->left = l;
	p->right = r;
}


void find_Node(B_Node *root, int type, int id) {
	if (!root);

	else if (root->id == id) {
		if (type == 1) {
			preorder(root);
		}
		else if (type == 2) {
			inorder(root);
		}
		else {
			postorder(root);
		}
	}
	else {
		find_Node(root->left, type, id);
		find_Node(root->right, type, id);
	}
}

void preorder(B_Node *root) {
	if (!root) {
		return;
	}
	printf(" %d", root->data);
	preorder(root->left);
	preorder(root->right);
}

void inorder(B_Node *root) {
	if (!root) {
		return;
	}
	inorder(root->left);
	printf(" %d", root->data);
	inorder(root->right);

}
void postorder(B_Node *root) {
	if (!root) {
		return;
	}
	postorder(root->left);
	postorder(root->right);
	printf(" %d", root->data);
}