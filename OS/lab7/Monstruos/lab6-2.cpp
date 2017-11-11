#include <cstdlib>
#include <cstdio>
#include <pthread.h>

pthread_mutex_t lock;
int A = 0;

void *func(void *arg) {
	int num = (int)arg;
	while(1) {
		pthread_mutex_lock(&lock);
		A++;
		printf("[%d] %d", num, A);
		pthread_mutex_unlock(&lock);
	}
}

int main(int argc, char const *argv[])
{
	pthread_t thr1, thr2;
	int fst = 1;
	int snd = 2;
	pthread_mutex_init(&lock, NULL);
	pthread_create(&thr1, NULL, func, (void*)fst);
	pthread_create(&thr2, NULL, func, (void*)snd);
	pthread_join(thr1, NULL);
	pthread_join(thr2, NULL);
	pthread_mutex_destroy(&lock);
	return 0;
}