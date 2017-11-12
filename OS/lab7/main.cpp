#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

using namespace std;

int i = 0;

void* f(void* arg)
{
	int num = *((int*)arg);
	while(1)
	{
		i++;
		printf("%d(%d)\n", i, num);
		fflush(0);
	}
}

int main()
{
	pthread_t th1, th2;
	
	int num1 = 1, num2 = 2;
	pthread_create(&th1, NULL, f, (void *)&num1);
	pthread_create(&th2, NULL, f, (void *)&num2);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	return 0;
}
