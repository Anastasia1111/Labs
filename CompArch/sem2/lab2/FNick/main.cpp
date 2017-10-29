#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

using namespace std;

int mult(int* m1i, int* m2j, int n)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
		sum += m1i[i] * m2j[i];
	return sum;
}

int main()
{
	int matrixSize[3];
	srand(time(NULL));
	
	cout << "Line number (matrix 1): ";
	cin >> matrixSize[0];
	int** matrix1 = new int*[matrixSize[0]];
	cout << "Column number (matrix 1): ";
	cin >> matrixSize[1];
	int n = matrixSize[0] * matrixSize[1];
	for (int i = 0; i < matrixSize[0]; ++i)
	{
		matrix1[i] = new int[matrixSize[1]];
		for (int j = 0; j < matrixSize[1]; ++j)
		{
			matrix1[i][j] = rand() % (3 * n);
			cout << matrix1[i][j] << "\t";
		}
		cout << endl;
	}
	
	cout << "Line number (matrix 2): " << matrixSize[1] << endl;
	int** matrix2 = new int*[matrixSize[1]];
	cout << "Column number (matrix 2): ";
	cin >> matrixSize[2];
	n = matrixSize[1] * matrixSize[2];
	for (int i = 0; i < matrixSize[1]; ++i)
	{
		matrix2[i] = new int[matrixSize[2]];
		for (int j = 0; j < matrixSize[2]; ++j)
		{
			matrix2[i][j] = rand() % (3 * n);
			cout << matrix2[i][j] << "\t";
		}
		cout << endl;
	}
	int** tempMatrix = new int*[matrixSize[2]];
	for (int i = 0; i < matrixSize[2]; ++i)
	{
		tempMatrix[i] = new int[matrixSize[1]];
		for (int j = 0; j < matrixSize[1]; ++j)
			tempMatrix[i][j] = matrix2[j][i];
	}
	matrix2 = tempMatrix;
	
	int threadNumber;
	cout << "Thread number (from 2 to " << (matrixSize[0] * matrixSize[2]) << "): ";
	cin >> threadNumber;
	
	pthread_t* thread = new pthread_t[threadNumber];
	
	cout << "M1 * M2 =" << endl;
	int** matrix = new int*[matrixSize[0]];
	for (int i = 0; i < matrixSize[0]; ++i)
	{
		matrix[i] = new int[matrixSize[2]];
		for (int j = 0; j < matrixSize[2]; ++j)
		{
			matrix[i][j] = mult(matrix1[i], matrix2[j], matrixSize[1]);
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	return 0;
}
