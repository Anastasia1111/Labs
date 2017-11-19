#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include <string.h>
#include <ctime>

using namespace std;

void multiplication(float **A, float **B, float **R, int size, int start_thr = 0,int num_of_threads = 1);

typedef struct{
	float **A;
	float **B;
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
	printf("Open savefile...");
	FILE *out = fopen(str, "a");
	if(out == NULL) {
		printf("Error.\n");
		return 1;
	}
	fprintf(out, "%d\t%d\t", n, thread_num);
	printf("Complete.\n");

	printf("Memory allocation...");
	float **A = new float *[n];
	float **B = new float *[n];
	float **res = new float *[n];
	for(i = 0; i < n; ++i) {
		A[i] = new float [n];
		B[i] = new float [n];
		res[i] = new float [n];
		if(A[i] == NULL) {
			printf("Error(A, %d str).\n", i);
			return 1;
		}
		if(B[i] == NULL) {
			printf("Error(B, %d str).\n", i);
			return 1;
		}
		if(res[i] == NULL) {
			printf("Error(Res, %d str).\n", i);
			return 1;
		}
	}
	printf("Complete.\n");
	printf("Starting...\n");
		
	params p;
	p.A = A;
	p.B = B;
	p.R = res;
	p.size = n;
	p.num_of_threads = thread_num;
	p.start_thr = 0;
	printf("Making thread parameters...");
	params *pth = new params[thread_num];
	if(pth == NULL) {
		printf("Error.\n");
		return 1;
	}
	for(i = 0; i < thread_num; ++i) {
		pth[i] = p;
		pth[i].start_thr = i;
	}
	printf("Complete.\n");
	
	printf("Making thread descriptions...");
	pthread_t *thread = new pthread_t[thread_num];
	if(thread == NULL) {
		printf("Error.\n");
		return 1;
	}
	printf("Complete.\n");
	printf("Matrixes determination...");
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j) {
			A[i][j] = ((float)((rand() % (2*n)) + n))/((rand() % n) + 1);
			B[i][j] = ((float)((rand() % (2*n)) + n))/((rand() % n) + 1);
			res[i][j] = 0;
		}
	}
	printf("Complete.\n");

	clock_t start, time;
	double t;
	for(int w = 0; w < 5; w++) {
		start = clock();
		printf("Thread creating...\n");
		for(i = 0; i < thread_num; ++i) {
			if ( pthread_create( thread+i, NULL, thread_func, (void *)(pth+i) ) ) {
				printf("Error(thread #%d).\n", i);
				return EXIT_FAILURE;
			}
		}
		printf("Complete thread creating.\n");
		for(i = 0; i < thread_num; ++i)
			if ( pthread_join( thread[i], NULL ) ) {
				printf("Error(Failed to join thread #%d)\n", i);
				return EXIT_FAILURE;
			}
		time = clock() - start;
		t = ((double)time)/CLOCKS_PER_SEC;
		printf("Complete caluclating.\n");
		fprintf(out, "%f\t", t);
		printf("Complete %d%%...\n", (w+1)*20);
	}

	printf("Writing results into file...");
	fprintf(out, "\n");
	printf("Time of last trying: %f\n", t);
	for(i = 0; i < n; ++i) {
		delete A[i];
		delete B[i];
	}
	delete A;
	delete B;
	fclose(out);
	return 0;
}

void multiplication(float **A, float **B, float **R, int size, int start_thr,int num_of_threads) {
	int a, b, i;
	printf("Thread #%d is calculating.\n", start_thr);
	for(a = start_thr; a < size; a += num_of_threads) {
		for(b = 0; b < size; ++b) {
			for(i = 0; i < size; ++i) {
				R[a][i] += A[a][b] * B[b][i];
			}
		}
	}
	printf("Thread #%d complete calculating.\n", start_thr);
	return;
}
