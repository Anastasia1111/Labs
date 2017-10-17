#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int fds[2];
	if(pipe(fds)) {
		write(STDOUT_FILENO, "Pipe fail.\n", 11);
		return 1;
	}
	switch(fork())
	{
		case 0: {
			/*Child*/
			close(fds[1]);
			char a[250];
			for(int i = 0; i < strlen(a); ++i)
				a[i] = 0;
			int len;
			while((len = read(fds[0], a, sizeof(a))) != 0){

			}
			printf("Child received %d symbols: %s", strlen(a), a);
			/*for(int i = 0; i < 30; ++i) {
				printf("a[%d] = %d\n", i, a[i]);
			}*/
			close(fds[0]);
			break;
		}
		default: {
			/*Parent*/
			close(fds[0]);
			char a[] = "Hello, world ";
			write(fds[1], a, strlen(a) + 1);
			close(fds[1]);
			wait(0);
		}
	}
	return 0;
}