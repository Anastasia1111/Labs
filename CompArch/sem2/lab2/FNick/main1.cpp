#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <pthread.h>

using namespace std;

struct thrData
{
	int i;
	int j;
	thrData* next;
};

int** matrix1;
int** matrix2;
int** matrix;
int matrixSize[3];

void* mult(void* arg)
{
	thrData* data = (thrData*) arg;
	while(data != NULL)
	{
		int sum = 0;
		int* m1i = matrix1[data->i];
		int* m2j = matrix2[data->j];
		for (int i = 0; i < matrixSize[1]; ++i)
			sum += m1i[i] * m2j[i];
		matrix[data->i][data->j] = sum;
		data = data->next;
	}
}

int main()
{
	srand(time(NULL));
	
	FILE* out = fopen("./res1.tsv", "w+");
	
	int k = 1;
	while(1)
	{
		matrixSize[0]=matrixSize[1]=matrixSize[2]=k;
		matrix1 = new int*[matrixSize[0]];
		int n = matrixSize[0] * matrixSize[1];
		for (int i = 0; i < matrixSize[0]; ++i)
		{
			matrix1[i] = new int[matrixSize[1]];
			for (int j = 0; j < matrixSize[1]; ++j)
				matrix1[i][j] = rand() % (3 * n);
		}
		
		matrix2 = new int*[matrixSize[1]];
		n = matrixSize[1] * matrixSize[2];
		for (int i = 0; i < matrixSize[1]; ++i)
		{
			matrix2[i] = new int[matrixSize[2]];
			for (int j = 0; j < matrixSize[2]; ++j)
				matrix2[i][j] = rand() % (3 * n);
		}
		int** tempMatrix = new int*[matrixSize[2]];
		for (int i = 0; i < matrixSize[2]; ++i)
		{
			tempMatrix[i] = new int[matrixSize[1]];
			for (int j = 0; j < matrixSize[1]; ++j)
				tempMatrix[i][j] = matrix2[j][i];
		}
		delete matrix2;
		matrix2 = tempMatrix;
		
		int start = clock();
		
		pthread_t* thread = new pthread_t[2];
		thrData** index = new thrData*[2];
		for(int i = 0; i < 2; ++i)
			index[i] = NULL;
			
		matrix = new int*[matrixSize[0]];
		for (int i = 0; i < matrixSize[0]; ++i)
		{
			matrix[i] = new int[matrixSize[2]];
			for (int j = 0; j < matrixSize[2]; ++j)
			{
				thrData* newIndex = new thrData;
				newIndex->i = i;
				newIndex->j = j;
				newIndex->next = index[(i * matrixSize[2] + j) % 2];
				index[(i * matrixSize[2] + j) % 2] = newIndex;
			}
		}
		for (int i = 0; i < 2; ++i)
			pthread_create(&thread[i], NULL, mult, (void*)index[i]);
		for (int i = 0; i < 2; ++i)
			pthread_join(thread[i], NULL);
			
		int finish = clock();
		fprintf(out, "%f\t", (float)(finish - start)/CLOCKS_PER_SEC);
		printf("%d\n", k);
		delete matrix;
		delete matrix1;
		delete matrix2;
		++k;
	}
	return 0;
}
