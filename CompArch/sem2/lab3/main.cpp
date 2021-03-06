#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <mpi.h>

int* M1;
int* M2;
int* Res;
int Size;
int ThrNum;
int rank;

int main(int argc, char* argv[])
{
	Size = atoi(argv[1]);
	
	srand(time(NULL));
	
	int size = Size * Size;
	
	M1 = new int[size];
	M2 = new int[size];
	Res = new int[size];
	for (int i = 0; i < Size; ++i)
		for (int j = 0; j < Size; ++j)
		{
			M1[i * Size + j] = rand() % (3 * size);
			M2[i * Size + j] = rand() % (3 * size);
			Res[i * Size + j] = 0;
		}
	
	double time, total_time = 0.0;
	timespec start, finish;
	
	clock_gettime(CLOCK_MONOTONIC, &start);
		
	MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &ThrNum);
	
	int bandSize = 0, first = 0, last = 0;
	for (int i = 0; i <= rank; ++i)
	{
		first += bandSize;
		bandSize = ceil((float)size / (ThrNum - i));
		size -= bandSize;
		last = first + bandSize - 1;
	}
	
	for (int k = first; k <= last; ++k)
	{
		int i = k / Size;
		int j = k % Size;
		for (int r = 0; r < Size; ++r)
			Res[k] += M1[i * Size + r] * M2[j * Size + r];
	}
	
	MPI_Finalize();
		
	clock_gettime(CLOCK_MONOTONIC, &finish);
	
	time = (finish.tv_sec - start.tv_sec) + ((finish.tv_nsec - start.tv_nsec) * 1.0) / 1000000000;
	printf("%f\n", time);
	
	return 0;
}
