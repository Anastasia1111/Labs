#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

using namespace std;

int i = 0;

//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t lock = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
pthread_mutex_t lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;

#define LOCK pthread_mutex_lock(&lock);
#define UNLOCK pthread_mutex_unlock(&lock);

void* f(void* arg)
{
	int num = *((int*)arg);
	LOCK
	int err = LOCK
		i++;
		printf("%d(%d)(%d)\n", i, num, err);
		fflush(0);
	UNLOCK
}

int main()
{
	pthread_t th1, th2;
	
	int num1 = 1, num2 = 2;
	while(1)
	{
		pthread_create(&th1, NULL, f, (void *)&num1);
		pthread_create(&th2, NULL, f, (void *)&num2);
		pthread_join(th1, NULL);
		pthread_join(th2, NULL);
	}
	return 0;
}
