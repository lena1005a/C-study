#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main() {
	int n, *A, *B, tmp, index;

	scanf("%d", &n);
	A = (int *)malloc(sizeof(int)*n);
	B = (int *)malloc(sizeof(int)*n);

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		A[i] = rand();
		B[i] = A[i];
	}


	//미리 역정렬 시키기(선택정렬 사용)
	for (int i = n - 1; i >= 1; i--) {
		index = i;
		for (int j = i - 1; j >= 0; j--) {
			if (A[index] > A[j]) index = j;
		}
		tmp = A[index];
		A[index] = A[i];
		A[i] = tmp;
	}
	for (int i = n - 1; i >= 1; i--) {
		index = i;
		for (int j = i - 1; j >= 0; j--) {
			if (B[index] > B[j]) index = j;
		}
		tmp = B[index];
		B[index] = B[i];
		B[i] = tmp;
	}

	//////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	QueryPerformanceFrequency(&ticksPerSec); //선택정렬
	QueryPerformanceCounter(&start);

	for (int i = n - 1; i >= 1; i--) {
		index = i;
		for (int j = i - 1; j >= 0; j--) {
			if (A[index] < A[j]) index = j;
		}
		tmp = A[index];
		A[index] = A[i];
		A[i] = tmp;
	}

	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

	///////////////////////////////////////////////////////////////////////////

	QueryPerformanceFrequency(&ticksPerSec); //삽입정렬
	QueryPerformanceCounter(&start);

	for (int i = 1; i < n; i++) { //i=6
		index = i;
		for (int j = i - 1; j >= 0; j--) {
			if (B[i] < B[j]) index = j;
			else break;
		}
		tmp = B[i];
		for (int k = i; k > index; k--) {
			B[k] = B[k - 1];
		}
		B[index] = tmp;

	}

	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);


	return 0;
}