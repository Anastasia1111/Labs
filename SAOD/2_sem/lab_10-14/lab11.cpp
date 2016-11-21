#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void InsertSort(double* P, int *A, int n)
{
	int i, j;
	double t1;
	int t2;
	for (i = 1; i < n; i++) {
		t1 = P[i]; 
		t2 = A[i];
		for (j = i - 1; (j >= 0) && (t1 >= P[j]); j--)
		{
			P[j+1] = P[j];
			A[j+1] = A[j];
		}
		P[j+1] = t1;
		A[j+1] = t2;
	}
}

void p_calc_n_sort(double *P, int* A, int n, char *message)
{
	int k;
	int i = 0;
	int j;
	for(k = 0; k < n; ++k)
	{
		P[k] = 0;
	}
	while (message[i] != 0)
	{
		j = message[i];
		P[j-32] = P[j-32] + 1;
		++i;
	}
	for (k = 0; k < n; k++)
	{
		P[k] = P[k]/(double)i;
	}
	InsertSort(P, A, n);
}

main()
{
	int i, j;
	int n = 94;
	int A[n];
	double P[n];
	double Q[n];
	int L[n];
	char C[n][n/2];
	char message[] = "hhh89897iujhkkjkkjvjhkjkljhkk h kgkg kgk hk gghg9y7897877856dybcc  jv j 77868u f f788ehdkjdkdhdhsdfkhsdkdslhflsdvvnf  jdfjhdfjhbjxcvxcvjhxcvjhxcvjhxcv vbjsvbkd gk";
	
	int k;
	for (k = 0; k < n; k++)
	{
		P[k] = 0.0;
		L[k] = 0;
		A[k] = k + 32;
	}
	/*
	p_calc_n_sort(P, A, n, message);
	P[0] = Q[0] = 0.0;
	for(i = 1; i <= n; ++i)
	{
		Q[i] = Q[i-1] + P[A[i-1]];
		L[i] = (int) (-(log(P[A[i]])/log(2)) + 1);
		if(L[i] < 1) L[i] = 0;
		
	}
	for(i = 1; i <= n; ++i)
	{
		for(j = 1; j <= L[i]; ++j)
		{
			Q[i-1] = Q[i-1] * 2;
			C[A[i]][j] = (char)((int)Q[i-1] + 48);
			if(Q[i-1] > 1)
			{
				Q[i-1] = Q[i-1] - 1;
			}
		}
		C[A[i]][L[i]+1] = 0;
	}
	
	for(i = 1; i <= n; ++i)
	{
		printf("\n%i. ", A[i]);
		for(j = 1; j <= L[i]; ++j)
		{
			printf("%c", C[A[i]][j]);
		}
	}*/
	
	p_calc_n_sort(P, A, n, message);
	
	Q[0] = 0.0;
	for(i = 1; i <= n; ++i)
	{
		Q[i] = Q[i-1] + P[i-1];
		L[i] = (int) (-(log2(P[i])) + 1);
		if(L[i] < 1) 
			L[i] = 0;
	}
	
	for(i = 1; i < n; ++i)
	{
		for(j = 1; j <= L[i]; ++j)
		{
			Q[i-1] = Q[i-1] * 2;
			C[i][j] = (char) (Q[i-1] + 48);
			if(Q[i-1] > 1)
				Q[i-1] = Q[i-1] - 1;
		}
		
		C[i][L[i]+1] = 0;
	}
	
	for(i = 1; i < n; ++i)
	{
		printf("%4c.  %1.4f  %2i  ", A[i], P[i], L[i]);
		for(j = 1; j <= L[i]; ++j)
		{
			printf("%c", C[i][j]);
		}
		
		printf("\n");
	}
	
	double h = 0, ml = 0;
	for(i = 1; i < 94; ++i)
	{
		if(P[i] > 0.00000000001)
			h += -1*P[i] * log2(P[i]);
		ml += L[i] * P[i-1];
	}
	printf("\nEntropia: %1.4f, Mid length: %1.4f",h,ml);
	
	system("pause");
	return 0;
}
