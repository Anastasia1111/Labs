#include <stdlib.h>
#include <stdio.h>

const int size = 3;
float arr[size][size+1] = {-2, 1, -1, -1, 
							1, -1, 2, 3,
							3, 2, -2, -2};
float ans[size] = {0, 0, 0};

void swap(int fst, int sec)
{
	int i;
	float buff;
	for(i = 0; i < (size + 1); ++i)
	{
		buff = arr[fst][i];
		arr[fst][i] = arr[sec][i];
		arr[sec][i] = buff;
	}
}

int compare(int colNum)
{
	float buff = arr[colNum][colNum];
	int i;
	int num = colNum;// number of row with max "a"
	for(i = colNum + 1; i < size; ++i)
	{
		if(arr[i][colNum] > buff)
		{
			buff = arr[i][colNum];
			num = i;
		}
	}
	return num;
}

int main()
{
	int i, j, k;
	int numer;
	float q;
	
	for(i = 0; i < size-1; ++i)
	{
		numer = compare(i);
		if(numer != i)
			swap(numer, i);
		for(j = i+1; j < size; ++j)
		{
			q = arr[j][i]/arr[i][i];
			for(k = i; k <= size; ++k)
			{
				arr[j][k] -= q*arr[i][k];
			}	
		}
	}
	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < size+1; ++j)
			printf("%4.2f ", arr[i][j]);
		printf("\n");
	}
	
	for(i = size-1; i >= 0; --i)
	{
		q = arr[i][size];
		for(j = i+1; j < size; ++j)
		{
			q -= arr[i][j] * ans[j];
		}
		ans[i] = q/arr[i][i];
	}
	
	printf("\nAnswers:\n");
	for(j = 0; j < size; ++j)
		printf("x%d = %4.2f\n", j, ans[j]);
	
	system("pause");
	return 0;
}
