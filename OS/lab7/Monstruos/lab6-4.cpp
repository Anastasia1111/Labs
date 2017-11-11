#include <cstdlib>
#include <cstdio>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;
int A = 0;

void *func(void *arg) {
	int num = (int)arg;
	while(1) {
		sem_wait(&sem);
		A++;
		printf("[%d] %d", num, A);
		sem_post(&sem);
	}
}

int main(int argc, char const *argv[])
{
	pthread_t thr1, thr2, thr3;
	int fst = 1;
	int snd = 2;
	int thd = 3;
	sem_init(&sem, NULL, 2);
	pthread_create(&thr1, NULL, func, (void*)fst);
	pthread_create(&thr2, NULL, func, (void*)snd);
	pthread_create(&thr3, NULL, func, (void*)thd);
	pthread_join(thr1, NULL);
	pthread_join(thr2, NULL);
	pthread_join(thr3, NULL);

	return 0;
}