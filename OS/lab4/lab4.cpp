#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>


void *func(void *arg)
{
	while(1)
		write(1,(char *)arg, 1);
	return arg;
}

int main()
{
	pthread_t th1, th2;
	char id = 'a';
	pthread_create (&th1, NULL, func, &id);
	char id1 = 'b';
	pthread_create (&th2, NULL, func, &id1);
	pthread_join(th1, NULL);
	return 0;
}
