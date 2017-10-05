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
	signal(SIGUSR1, handler);
}

int main()
{
	handler(1);
	pthread_t th1;
	pthread_create (&th1, NULL, func, &c);
	char but;
	while (1)
	{
		but = getchar();
		if (but == ' ') raise(SIGUSR1);
	}
	return 0;
}
