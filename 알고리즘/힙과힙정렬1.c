#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//배열(순차힙):연결트리(열결힙) , 삽입식(키가 미리주어지거나 차례로 주어지는):상향식(키가 미리주어진)
//조건: 삽입식(제자리) 힙, 최대 힙(힙은 내림차순. 리스트는 오른차순정렬 but정렬문제는아님. 단순구현문제),
//조건: 배열(순차힙)로 풀이, 추가메모리 O(1)
//삽입식 ->외부노드 필요없음

int n = 0;
int H[99]; //0번자리 비우기

void insertitem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();

void main() {
	//마지막노드 자리가 n, 추가자리 n+1, 삭제는 n
	char op_type;
	int key;

	while (1) {
		scanf("%c", &op_type);
		if (op_type == 'i') {
			scanf("%d", &key);
			if (n >= 99) continue;
			insertitem(key);
			printf("0\n");
		}
		else if (op_type == 'd') printf("%d\n", removeMax());
		else if (op_type == 'p') {
			if (n < 1) {
				getchar();
				continue;
			}
			printHeap();
		}
		else return;
		getchar();
	}
}


void insertitem(int key) {
	//라스트노드를 오른쪽으로 새로 옮기고(advanceLast)
	//expandExternal로 마지막에 노드붙이고
	//upHead으로 위치찾기 (스왑)
	n += 1;
	H[n] = key;
	upHeap(n);
}

int removeMax() {
	//맨위 삭제, 대신 맨마지막노드로 맨위루트 자리채움
	//맨마지막이엇떤 자리는 외부노드가되게끔.(reduceExternal 내부노드형식이 외부노드로변경)
	//downHead함수로 두자식중 더큰거랑 바꿈->반복
	if (n == 0) return 0;

	int key = H[1];
	H[1] = H[n];
	H[n] = 0;
	n -= 1;
	downHeap(1);
	return key;
	//삭제후 마지막노드를 갱신하는 작업은 retreatLast)
}

void upHeap(int i) { //6
	//재귀방식
	// 루트면 또는 부모노드키보다 작으면 반환,아니면 나와 부모를 스왑, 부모 uphead함수재귀
	if (i == 1 || (H[i] <= H[i / 2])) return;
	int tmp = H[i];
	H[i] = H[i / 2];
	H[i / 2] = tmp;
	upHeap(i / 2);
}
void downHeap(int i) {
	if (2 * i > n) return;
	if (H[2 * i] < H[i] && H[2 * i + 1] < H[i]) return;


	int small = (2 * i), tmp;
	if (H[2 * i] <= H[(2 * i) + 1]) {
		small = (2 * i) + 1;
	}
	tmp = H[small];
	H[small] = H[i];
	H[i] = tmp;

	downHeap(small);
}

void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}printf("\n");
}