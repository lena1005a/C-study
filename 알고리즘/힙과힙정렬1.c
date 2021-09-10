#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//�迭(������):����Ʈ��(������) , ���Խ�(Ű�� �̸��־����ų� ���ʷ� �־�����):�����(Ű�� �̸��־���)
//����: ���Խ�(���ڸ�) ��, �ִ� ��(���� ��������. ����Ʈ�� ������������ but���Ĺ����¾ƴ�. �ܼ���������),
//����: �迭(������)�� Ǯ��, �߰��޸� O(1)
//���Խ� ->�ܺγ�� �ʿ����

int n = 0;
int H[99]; //0���ڸ� ����

void insertitem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();

void main() {
	//��������� �ڸ��� n, �߰��ڸ� n+1, ������ n
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
	//��Ʈ��带 ���������� ���� �ű��(advanceLast)
	//expandExternal�� �������� �����̰�
	//upHead���� ��ġã�� (����)
	n += 1;
	H[n] = key;
	upHeap(n);
}

int removeMax() {
	//���� ����, ��� �Ǹ��������� ������Ʈ �ڸ�ä��
	//�Ǹ������̾��� �ڸ��� �ܺγ�尡�ǰԲ�.(reduceExternal ���γ�������� �ܺγ��κ���)
	//downHead�Լ��� ���ڽ��� ��ū�Ŷ� �ٲ�->�ݺ�
	if (n == 0) return 0;

	int key = H[1];
	H[1] = H[n];
	H[n] = 0;
	n -= 1;
	downHeap(1);
	return key;
	//������ ��������带 �����ϴ� �۾��� retreatLast)
}

void upHeap(int i) { //6
	//��͹��
	// ��Ʈ�� �Ǵ� �θ���Ű���� ������ ��ȯ,�ƴϸ� ���� �θ� ����, �θ� uphead�Լ����
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