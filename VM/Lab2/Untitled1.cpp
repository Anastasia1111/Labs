#include <stdlib.h>
#include <stdio.h>

const int size = 3;
const int iter = 8;
float arr[size][size+1] = {5, -1, 2, 3, 
							-2, -10, 3, -4,
							1, 2, 5, 12};
float ans[size] = {0, 
				   0, 
				   0};				
float bufans [size] = {0, 
					   0, 
					   0};

int main()
{
	int i, j, k;
	float multi;
	float buff;
	
	for(i = 0; i < size; ++i)
	{
		buff = arr[i][i];
		for(j = 0; j < size + 1; ++j)
		{
			arr[i][j] /= buff;
		}
		arr[i][i] -= 1;
	}
	
	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < size+1; ++j)
			printf("%4.2f ", arr[i][j]);
		printf("\n");
	}
	puts("\n");
	
	multi = 0;
	for(k = 0; k < iter; ++k)
	{
		for(i = 0; i < size; ++i)
		{
			for(j = 0; j < size; ++j)
			{
				multi += arr[i][j] * ans[j];
			}
			bufans[i] = arr[i][size] - multi;
			multi = 0;
		}
		for(i = 0; i < size; ++i)
			ans[i] = bufans[i];
		printf("%d iter:", k + 1);
		for(j = 0; j < size; ++j)
		{
			printf("x%d = %f, ", j+1, ans[j]);
		}
		printf("\b\b.\n");
	}
	
	system("pause");
	return 0;
}
