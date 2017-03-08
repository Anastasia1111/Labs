#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const int size = 3;
double arr[size][size+1] = {5, -1, 2, 3, 
							-2, -10, 3, -4,
							1, 2, 5, 12};
double ans[size] = {0, 
				   0, 
				   0};				
double bufans [size] = {0, 
					   0, 
					   0};
					   
double maximum(int lbor = 0, int rbor = size + 1, int upbor = 0, int downbor = size)
{
	double buff = 0;
	double end = 0;
	for(int i = upbor; i < downbor; ++i)
	{
		buff = 0;
		for(int j = lbor; j < rbor; ++j)
		{
			buff += fabs(arr[i][j]);
		}
		if(fabs(buff) > fabs(end))
			end = buff;
	}
	return end;
}

int main()
{
	int i, j, k;
	double multi;
	double buff;
	
	double accur;
	
	printf("accur:");
	scanf("%lf", &accur);
	
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
	
	double normc = maximum(0,size);
	double normb = maximum(size,size+1);
	//printf("normc = %f, normb = %f\n", normc, normb);
	
	double r = (accur * (1 - normc)) / normb; 
	
	int N = (int)(log(r)/log(normc)) + 1;
	//printf("r = %f, log(r) = %f, log(normc) = %f, N = %d\n", r, log(r), log(normc), N);
	
	multi = 0;
	for(k = 0; k < N; ++k)
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
