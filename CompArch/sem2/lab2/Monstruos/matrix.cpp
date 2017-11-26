#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include <string.h>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void multiplication(float *A, float *B, float **R, int size, int start_thr = 0,int num_of_threads = 1);

typedef struct{
	float *A;
	float *B;
	float **R;
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



int main(int argc, char *argv[]) {

	srand(time(NULL));
	int i, j;
	int n;
	int thread_num;
	char str[256];

	n = atoi(argv[1]);
	thread_num = atoi(argv[2]);

	sprintf(str, "./results.tsv");
	FILE *out = fopen(str, "a");
	if(out == NULL) {
		printf("Error.\n");
		return 1;
	}
	fprintf(out, "%d\t%d\t", n, thread_num);

	float *A = new float [n*n];
	float *B = new float [n*n];
	float **res = new float *[n];
	for(i = 0; i < n; ++i) {
		res[i] = new float [n];
		if(res[i] == NULL) {
			printf("Error(Res, %d str).\n", i);
			return 1;
		}
	}
		
	params p;
	p.A = A;
	p.B = B;
	p.R = res;
	p.size = n;
	p.num_of_threads = thread_num;
	p.start_thr = 0;
	params *pth = new params[thread_num];
	if(pth == NULL) {
		printf("Error.\n");
		return 1;
	}
	for(i = 0; i < thread_num; ++i) {
		pth[i] = p;
		pth[i].start_thr = i;
	}
	pthread_t *thread = new pthread_t[thread_num];
	if(thread == NULL) {
		printf("Error.\n");
		return 1;
	}
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j) {
			A[i*n + j] = ((float)((rand() % (2*n)) + n))/((rand() % n) + 1);
			B[i*n + j] = ((float)((rand() % (2*n)) + n))/((rand() % n) + 1);
			res[i][j] = 0;
		}
	}

	double t;
	duration<double> time_span;
	for(int w = 0; w < 1; w++) {
		auto begin = chrono::high_resolution_clock::now();
		for(i = 0; i < thread_num; ++i) {
			if ( pthread_create( thread+i, NULL, thread_func, (void *)(pth+i) ) ) {
				printf("Error(thread #%d).\n", i);
				return EXIT_FAILURE;
			}
		}
		for(i = 0; i < thread_num; ++i)
			if ( pthread_join( thread[i], NULL ) ) {
				printf("Error(Failed to join thread #%d)\n", i);
				return EXIT_FAILURE;
			}
		auto end = chrono::high_resolution_clock::now();
		time_span = duration_cast<duration<double>>(end - begin);
		cout << "Time of trying (chrono) " << time_span.count() << "sec." << endl;
		t = time_span.count();
		fprintf(out, "%f\t", t);
	}

	fprintf(out, "\n");
	delete A;
	delete B;
	for(int i = 0; i < n; ++i)
		delete res[i];
	delete res;
	fclose(out);
	return 0;
}

void multiplication(float *A, float *B, float **R, int size, int start_thr,int num_of_threads) {
	int a, b, i;
	for(a = start_thr; a < size; a += num_of_threads) {
		for(b = 0; b < size; ++b) {
			for(i = 0; i < size; ++i) {
				R[a][i] += A[a * size + b] * B[b * size + i];
			}
		}
	}
	return;
}
