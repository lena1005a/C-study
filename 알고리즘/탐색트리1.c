#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree {
	int key;
	struct tree *lChild, *rChild, *parent;
}T_node;

T_node *findRoot();
bool isRoot();

void insertItem();
T_node *treeSearch();
bool isExternal();
bool isInternal();
void expandExternal();

T_node *removeElement();
T_node *inOrderSucc();

void printTreePreOrd();


int main() {
	char op;
	int key;

	T_node *tree = (T_node *)malloc(sizeof(T_node));
	tree->parent = tree->lChild = tree->rChild = NULL;

	T_node *tmp;
	while (1) {
		scanf("%c", &op);
		switch (op) {
		case 'i':
			scanf("%d", &key);
			insertItem(tree, key);
			break;

		case 'd':
			scanf("%d", &key);
			tmp = treeSearch(tree, key);
			if (isInternal(tmp)) {
				tree = removeElement(tmp);
				printf("%d\n", key);
			}
			else printf("X\n");
			break;

		case 's':
			scanf("%d", &key);
			tmp = treeSearch(tree, key);
			if (isInternal(tmp)) printf("%d\n", tmp->key);
			else printf("X\n");
			break;

		case 'p':
			printTreePreOrd(tree);
			printf("\n");
			break;

		case 'q':
			return;

		default:
			break;
		}
		getchar();
		tree = findRoot(tree);
	}
}


bool isRoot(T_node *node) {
	if (node->parent == NULL) return true;
	return false;
}
T_node *findRoot(T_node *node) {
	while (!isRoot(node)) node = node->parent;
	return node;
}


void insertItem(T_node *root, int key) {
	T_node *tmp = treeSearch(root, key);
	if (isInternal(tmp)) return;
	tmp->key = key;
	expandExternal(tmp);
}

T_node *treeSearch(T_node *root_start, int key) {
	if (isExternal(root_start) || root_start->key == key) return root_start;
	else if (root_start->key > key) return treeSearch(root_start->lChild, key);
	else return treeSearch(root_start->rChild, key);
}


bool isExternal(T_node *node) {
	if (node->lChild == NULL) return true;
	return false;
}
bool isInternal(T_node *node) {
	return !isExternal(node);
}

void expandExternal(T_node *node) {
	T_node *R = (T_node *)malloc(sizeof(T_node));
	T_node *L = (T_node *)malloc(sizeof(T_node));
	node->rChild = R;
	node->lChild = L;
	R->parent = L->parent = node;
	R->lChild = R->rChild = L->lChild = L->rChild = NULL;
}


void printTreePreOrd(T_node *root_start) {
	if (isInternal(root_start)) {
		printf(" %d", root_start->key);
		printTreePreOrd(root_start->lChild);
		printTreePreOrd(root_start->rChild);
	}
}


T_node *removeElement(T_node *node) { 
	if (isExternal(node->lChild) && isInternal(node->rChild)) { 
		T_node *root = node->rChild;
		node->rChild->parent = node->parent;

		if (!isRoot(node)) {
			if (node->parent->rChild == node)
				node->parent->rChild = node->rChild;
			else
				node->parent->lChild = node->rChild;
		}
		free(node->lChild);
		free(node);
		return root;
	}
	else if (isExternal(node->rChild)) { 
		T_node *root = node->lChild;
		node->lChild->parent = node->parent;

		if (!isRoot(node)) {
			if (node->parent->rChild == node)
				node->parent->rChild = node->lChild;
			else
				node->parent->lChild = node->lChild;
		}

		free(node->rChild);
		free(node);
		return root;
	}
	else { //삭제할 노드의 두자식 모두 데이터를 가진 경우
		T_node *successor = inOrderSucc(node);
		node->key = successor->key;
		free(successor->lChild);
		successor->rChild->parent = successor->parent;
		if (successor->parent->rChild == successor)
			successor->parent->rChild = successor->rChild;
		else
			successor->parent->lChild = successor->rChild;
		free(successor);
		return node;
	}
}

T_node *inOrderSucc(T_node *node) {
	T_node *tmp = node->rChild;
	if (isExternal(tmp)) return NULL;
	while (isInternal(tmp)) tmp = tmp->lChild;
	return tmp->parent;
}