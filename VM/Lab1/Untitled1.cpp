#include <stdlib.h>
#include <stdio.h>

const int size = 3;
float arr[size][size+1] = {-2, 1, -1, -1, 
							1, -1, 2, 3,
							3, 2, -2, -2};
float ans[size] = {0, 0, 0};

int main()
{
	int i, j, k;
	float q;
	
	for(i = 0; i < size-1; ++i)
	{
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
