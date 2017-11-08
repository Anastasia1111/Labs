#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <ctime>

using namespace std;

void multiplication(int **A, int **B, int **R, int size, int start_thr = 0,int num_of_threads = 1);

typedef struct{
	int **A;
	int **B;
	int **R;
	int size;
	int start_thr;
	int num_of_threads;
} params;

static void* thread_func( void* vptr_args )
{
	params *args = (params *)vptr_args;
    multiplication(args->A, args->B, args->R, args->size, args->start_thr, args->num_of_threads);
    return NULL;
}



int main() {
	srand(time(NULL));
	int i, j;
	int n;
	int thread_num;
	cout << "size and number of threads:" << endl;
	cin >> n >> thread_num;
	int start = clock();
	int **A = new int *[n];
	int **B = new int *[n];
	int **res = new int *[n];
	for(i = 0; i < n; ++i) {
		A[i] = new int [n];
		B[i] = new int [n];
		res[i] = new int [n];
		for(j = 0; j < n; ++j) {
			A[i][j] = (rand() % 2*n) + n;
			B[i][j] = (rand() % 2*n) + n;
			res[i][j] = 0;
		}
	}
	
	/*for(i = 0; i < n; ++i) {
		cout.width(6);
		for(j = 0; j < n; ++j)
			cout << A[i][j] << " |";
		cout << endl;
	}
	cout << endl << endl;
	
	for(i = 0; i < n; ++i) {
		cout.width(6);
		for(j = 0; j < n; ++j)
			cout << B[i][j] << " |";
		cout << endl;
	}
	cout << endl << endl;
	*/
	params p;
	p.A = A;
	p.B = B;
	p.R = res;
	p.size = n;
	p.num_of_threads = thread_num;
	p.start_thr = 0;
	params *pth = new params[thread_num];
	for(i = 0; i < thread_num; ++i) {
		pth[i] = p;
		pth[i].start_thr = i;
	}
	
	pthread_t *thread = new pthread_t[thread_num];
	
	for(i = 0; i < thread_num; ++i) {
		if ( pthread_create( thread+i, NULL, thread_func, (void *)pth+i ) )
			return EXIT_FAILURE;
	}
	
	for(i = 0; i < thread_num; ++i)
		if ( pthread_join( thread[i], NULL ) )
			return EXIT_FAILURE;
	/*
	for(i = 0; i < n; ++i) {
		cout.width(6);
		for(j = 0; j < n; ++j)
			cout << res[i][j] << " |";
		cout << endl;
	}*/
	
	int finish = clock();
	cout << "Time of working: " << (float)(finish - start)/CLOCKS_PER_SEC << endl;
	for(i = 0; i < n; ++i) {
		delete A[i];
		delete B[i];
	}
	delete A;
	delete B;
	return 0;
}

void multiplication(int **A, int **B, int **R, int size, int start_thr,int num_of_threads) {
	int a, b, i;
	for(a = start_thr; a < size; a += num_of_threads) {
		for(b = 0; b < size; ++b) {
			for(i = 0; i < size; ++i) {
				R[a][b] += A[a][i] * B[i][b];
			}
		}
	}
	return;
}
