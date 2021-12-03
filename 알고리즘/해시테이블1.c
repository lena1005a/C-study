#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hash();
void initBucketArray();
void insertItem();
int searchItem();
int deleteItem();
void printTable();

typedef struct bucket {
	int key;
	struct bucket *next;
} BCKT;

int main() {
	BCKT *table;
	int M, value;
	char op = '0';

	scanf("%d", &M);
	table = (BCKT *)malloc(sizeof(BCKT)*M);
	initBucketArray(table, M);

	while (op != 'e') {
		scanf(" %c", &op);
		switch (op) {
		case 'i':
			scanf("%d", &value);
			insertItem(table, M, value);
			break;
		case 's':
			scanf("%d", &value);
			printf("%d\n", searchItem(table, M, value));
			break;
		case 'd':
			scanf("%d", &value);
			printf("%d\n", deleteItem(table, M, value));
			break;
		case 'p':
			printTable(table, M);
			break;
		default:
			break;
		}
	}
}

int hash(int m, int key) {
	return key % m;
}

void initBucketArray(BCKT *table, int m) {
	for (int i = 0; i < m; i++)
		(table + i)->next = NULL;
}

void insertItem(BCKT *table, int m, int key) {
	BCKT *home = table + hash(m, key), *newBucket = (BCKT *)malloc(sizeof(BCKT));
	newBucket->key = key;
	newBucket->next = home->next;
	home->next = newBucket;
}

int searchItem(BCKT *table, int m, int key) {
	int position = 0;
	BCKT *tempBucket = (table + hash(m, key))->next;
	for (; tempBucket != NULL; tempBucket = tempBucket->next, position++)
		if (tempBucket->key == key) {
			position++;
			break;
		}
		else if (tempBucket->next == NULL) {
			position = 0;
			break;
		}
	return position;
}

int deleteItem(BCKT *table, int m, int key) {
	int position = 0;
	BCKT *priorBucket = table + hash(m, key);
	for (; priorBucket->next != NULL; priorBucket = priorBucket->next, position++)
		if (priorBucket->next->key == key) {
			position++;
			priorBucket->next = priorBucket->next->next;
			break;
		}
		else if (priorBucket->next->next == NULL) {
			position = 0;
			break;
		}
	return position;
}

void printTable(BCKT *table, int m) {
	BCKT *toRead;
	for (int i = 0; i < m; i++) {
		toRead = (table + i)->next;
		for (; toRead != NULL; toRead = toRead->next)
			printf(" %d", toRead->key);
	}
	printf("\n");
}