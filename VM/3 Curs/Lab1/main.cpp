#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>

int M, C;

void FillInc(int* A, int n)
{
	int i;
	for (i = 0; i<n; i++) A[i] = i + 1;
}

void FillDec(int* A, int n)
{
	int i;
	for (i = 0; i<n; i++) A[i] = n - i;
}

void FillRand(int* A, int n)
{
	int i;
	srand(time(0));
	for (i = 0; i<n; i++) A[i] = rand() % (5 * n + 1) - n;
}

int CheckSum(int* A, int n)
{
	int i, cs = 0;
	for (i = 0; i<n; i++) cs += A[i];
	return cs;
}

int RunNumber(int* A, int n)
{
	int i, rn = 1;
	for (i = 1; i<n; i++)
		if (A[i - 1]>A[i]) rn++;
	return rn;
}

void PrintMas(int* A, int n)
{
	int i;
	printf("\nMassiv: ");
	for (i = 0;i<n;i++) printf("%d ", A[i]);
}

void Output(int *A, int n)
{
	int chsum, rnum;
	PrintMas(A, n);
	chsum = CheckSum(A, n);
	//printf("\nCheck Summ: %d", chsum);
	rnum = RunNumber(A, n);
	//printf("\nRun Number: %d", rnum);
	//printf("\nAverage RN: %4.1f\n", (float)n / rnum);
}

void BubbleSortMC(int* A, int n)
{
	int i, j, t, m, c;
	m = c = 0;
	for (i = 0; i<n; i++) {
		for (j = n - 1; j>i; j--) {
			c++;
			if (A[j]>A[j - 1]) { t = A[j]; m++; A[j] = A[j - 1]; m++; A[j - 1] = t; m++; }
		}
	}
	printf("\nPractical M and C:\nM=%d C=%d", m, c);
}

void SelectSortMC(int* A, int n)
{
	int i, j, k, t, m, c;
	m = c = 0;
	for (i = 0; i<n - 1; i++) {
		k = i;
		for (j = i + 1; j<n; j++) {
			c++;
			if (A[j]>A[k]) k = j;
		}
		t = A[k]; m++; A[k] = A[i]; m++; A[i] = t; m++;
	}
	printf("\nPractical M and C:\nM=%d C=%d", m, c);
}

void merge(int* A, int left, int right)
{
	int n = (right - left);
	int* res = new int[n*2];
	int i = 0, j = 0;
	while (i < n && j < n)
	{
		C++; M++;
		if (A[left + i] > A[right + j])
		{
			res[i + j] = A[left + i];
			i++;
		}
		else {
			res[i + j] = A[right + j];
			j++;
		}
	}
	while (i < n)
	{
		M++;
		res[i + j] = A[left + i];
		i++;
	}
	while (j < n)
	{
		M++;
		res[i + j] = A[right + j];
		j++;
	}
	for (i = 0; i < n * 2; i++) {
		A[left + i] = res[i];
		M++;
	}
}

void MergeSortMC(int* A, int n)
{
	M = C = 0;
	for (int i = 1; i < n; i *= 2) {
		for (int j = 0; j < n - i; j += 2 * i) {
			merge(A, j, j + i);
		}
		Output(A, n);
	}
	printf("\nPractical M and C:\nM=%d C=%d", M, C);
}


int main()
{
	int *A, *B, n, i, m, c;
	printf("Razmer massiva: ");
	scanf_s("%d", &n);
	A = new int[n];
	B = new int[n];
	if (A == NULL) {
		printf(" ERROR ");
		return 1;
	}
	FillRand(A, n);
	for (i = 0; i < n; i++)
		B[i] = A[i];
	Output(A, n);
	printf("\n");
	/*printf("\nSorted:");
	SelectSortMC(A, n);
	Output(A, n);
	BubbleSortMC(B, n);
	Output(B, n);*/
	MergeSortMC(A, n);
	puts("");
	Output(A, n);
	delete A;
	delete B;
	A = NULL;
	system("Pause");
	return 0;
}

