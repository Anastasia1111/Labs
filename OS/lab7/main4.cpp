#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

int i = 0;

sem_t lock;

#define WAIT sem_wait(&lock);
#define UNLOCK sem_post(&lock);

void* f(void* arg)
{
	int num = *((int*)arg);
	WAIT
		int val;
		sem_getvalue(&lock, &val);
		i++;
		cout << i << "(" << num << ")(" << val << ")\n";
	UNLOCK
}

int main()
{
	pthread_t th1, th2, th3, th4;
	
	sem_init(&lock, 0, 4);
	
	int num1 = 1, num2 = 2, num3 = 3, num4 = 4;
	while(1)
	{
		pthread_create(&th1, NULL, f, (void *)&num1);
		pthread_create(&th2, NULL, f, (void *)&num2);
		pthread_create(&th3, NULL, f, (void *)&num3);
		pthread_create(&th4, NULL, f, (void *)&num4);
		pthread_join(th1, NULL);
		pthread_join(th2, NULL);
		pthread_join(th3, NULL);
		pthread_join(th4, NULL);
	}
	
	sem_destroy(&lock);
	return 0;
}
