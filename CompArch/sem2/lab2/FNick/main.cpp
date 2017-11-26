#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <pthread.h>

struct t_data
{
	int first;
	int last;
};

int* M1;
int* M2;
int* Res;
int Size;
int ThrNum;

void* mult(void* arg)
{
	t_data d = *((t_data*) arg);
	
	for (int k = d.first; k <= d.last; ++k)
	{
		int i = k / Size;
		int j = k % Size;
		for (int r = 0; r < Size; ++r)
			Res[k] += M1[i * Size + r] * M2[j * Size + r]; // Для чистоты эксперимента вторая матрица воспринимается как транспонированная
	}
}

int main(int argc, char* argv[])
{
	Size = atoi(argv[1]);
	ThrNum = atoi(argv[2]);
	
	srand(time(NULL));
	
	FILE* out = fopen("./res.tsv", "a");
	
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
	
	pthread_t* thread = new pthread_t[ThrNum];
	t_data* data = new t_data[ThrNum];
	
	int bandSize = 0, first = 0;
	for (int i = 0; i < ThrNum; ++i)
	{
		first += bandSize;
		bandSize = ceil((float)size / (ThrNum - i));
		size -= bandSize;
		data[i].first = first;
		data[i].last = first + bandSize - 1;
	}
	
	double time, total_time = 0.0;
	timespec start, finish;
	
	for (int k = 0; k < 5; ++k)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		
		for (int i = 0; i < ThrNum; ++i)
			pthread_create(&thread[i], NULL, mult, (void*)&data[i]);
		for (int i = 0; i < ThrNum; ++i)
			pthread_join(thread[i], NULL);
			
		clock_gettime(CLOCK_MONOTONIC, &finish);
		
		time = (finish.tv_sec - start.tv_sec) + ((finish.tv_nsec - start.tv_nsec) * 1.0) / 1000000000;
		total_time += time;
		
		printf("%f\n", time);
	}
	
	fprintf(out, "N = %d\tTN = %d\tM = %f\n", Size, ThrNum, total_time/5);
	
	return 0;
}
