#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	int fds[2];
	pipe(fds);
	char msg[80] = "Hello World!\n";
	switch(fork())
	{
		case 0:
			close(fds[1]);
			char buf[80];
			read(fds[0], buf, 80);
			write(1, buf, strlen(buf) - 2);
			break;
		default:
			write(fds[1], msg, strlen(msg));
			wait(0);
			break;
	}
	return 0;
}
