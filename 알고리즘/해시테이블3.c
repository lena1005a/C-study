#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hash();
int hash2();
void initBucketArray();
void insertItem();
int searchItem();
void printTable();


int main() {
	int M, n, value, q, *table;
	char op = '0';

	scanf("%d %d %d", &M, &n, &q);
	table = (int *)malloc(sizeof(int)*M);
	initBucketArray(table, M);

	while (op != 'e') {
		scanf(" %c", &op);
		switch (op) {
		case 'i':
			scanf("%d", &value);
			insertItem(table, M, value, q);
			break;
		case 's':
			scanf("%d", &value);
			searchItem(table, M, value, q);
			break;
		case 'p':
			printTable(table, M);
			break;
		default:
			printTable(table, M);
			break;
		}
	}
}

int hash(int m, int key) {
	return key % m;
}

int hash2(int q, int key) {
	return q - hash(q, key);
}

void initBucketArray(int *table, int m) {
	for (int i = 0; i < m; i++) table[i] = 0;
}

void insertItem(int *table, int m, int key, int q) {
	int index = hash(m, key);
	while (table[index] != 0) {
		printf("C");
		index = hash(m, index + hash2(q, key));
	}
	table[index] = key;
	printf("%d\n", index);
}

int searchItem(int *table, int m, int key, int q) {
	for (int index = hash(m, key); 1; index = hash(m, ++index))
		if (table[index] == key) {
			printf("%d %d\n", index, key);
			return;
		}
		else if (index == hash(m, m + hash(m, key) - 1)) {
			printf("-1\n");
			return;
		}
}


void printTable(int *table, int m) {
	for (int i = 0; i < m; i++) printf(" %d", table[i]);
	printf("\n");
}