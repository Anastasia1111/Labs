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
	
	FILE* out = fopen("./res.tsv", "w+");
	
	cout << "Line number (matrix 1): ";
	cin >> matrixSize[0];
	matrix1 = new int*[matrixSize[0]];
	cout << "Column number (matrix 1): ";
	cin >> matrixSize[1];
	int n = matrixSize[0] * matrixSize[1];
	for (int i = 0; i < matrixSize[0]; ++i)
	{
		matrix1[i] = new int[matrixSize[1]];
		for (int j = 0; j < matrixSize[1]; ++j)
		{
			matrix1[i][j] = rand() % (3 * n);
			//cout << matrix1[i][j] << "\t";
		}
		//cout << endl;
	}
	
	cout << "Line number (matrix 2): " << matrixSize[1] << endl;
	matrix2 = new int*[matrixSize[1]];
	cout << "Column number (matrix 2): ";
	cin >> matrixSize[2];
	n = matrixSize[1] * matrixSize[2];
	for (int i = 0; i < matrixSize[1]; ++i)
	{
		matrix2[i] = new int[matrixSize[2]];
		for (int j = 0; j < matrixSize[2]; ++j)
		{
			matrix2[i][j] = rand() % (3 * n);
			//cout << matrix2[i][j] << "\t";
		}
		//cout << endl;
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
	
	matrix = new int*[matrixSize[0]];
	for (int i = 0; i < matrixSize[0]; ++i)
		matrix[i] = new int[matrixSize[2]];
	
	int threadNumber;
	cout << "Max thread number (from 2 to " << (matrixSize[0] * matrixSize[2]) << "): ";
	cin >> threadNumber;
	
	for (int thn = threadNumber; thn <= threadNumber; ++thn)
	{
			
		pthread_t* thread = new pthread_t[thn];
		thrData** index = new thrData*[thn];
		for (int k = 0; k < 100; ++k)
		{
			int start = clock();
			for(int i = 0; i < thn; ++i)
				index[i] = NULL;
				
			for (int i = 0; i < matrixSize[0]; ++i)
			{
				for (int j = 0; j < matrixSize[2]; ++j)
				{
					thrData* newIndex = new thrData;
					newIndex->i = i;
					newIndex->j = j;
					newIndex->next = index[(i * matrixSize[2] + j) % thn];
					index[(i * matrixSize[2] + j) % thn] = newIndex;
				}
			}
			for (int i = 0; i < thn; ++i)
				pthread_create(&thread[i], NULL, mult, (void*)index[i]);
			for (int i = 0; i < thn; ++i)
				pthread_join(thread[i], NULL);
				
			int finish = clock();
			fprintf(out, "%f\t", (float)(finish - start)/CLOCKS_PER_SEC);
		}
		fprintf(out, "\n");
	}
	
	cout << "M1 * M2 =" << endl;
	for (int i = 0; i < matrixSize[0]; ++i)
	{
		for (int j = 0; j < matrixSize[2]; ++j);
			//cout << matrix[i][j] << "\t";
		//cout << endl;
	}
	return 0;
}
