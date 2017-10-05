#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

void *func(void *arg)
{
	while(1)
		write(1,(char *)arg, 1);
	return arg;
}

char c = 'b';

void handler (int signo)
{
	c = (c == 'a' ? 'b': 'a');
	signal(SIGALRM, handler);
	alarm(3);
}

int main()
{
	handler(1);
	pthread_t th1;
	pthread_create (&th1, NULL, func, &c);
	alarm(3);
	pthread_join(th1, NULL);
	return 0;
}

