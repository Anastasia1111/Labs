#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_USER 16

int sock[NUM_USER], listener;
int states[NUM_USER];

void *clientHandler(void *arg);

int main()
{
	pthread_t thr[NUM_USER]; 
	struct sockaddr_in addr;
	char buf[256];
	
	for(int i = 0; i < NUM_USER; ++i) {
		sock[i] = -1;
	}

	listener = socket(AF_INET, SOCK_STREAM, 0);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1337);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(listener, (struct sockaddr *)&addr, sizeof(addr));
	
	listen(listener, NUM_USER);
	printf("Starting:\n");
	int i;
	for(i = 0; i < NUM_USER; ++i)
	{
		states[i] = -1;
	}
	char hi[256] = "You are connected!";
	while(1) {
		for(i = 0; i < NUM_USER; ++i)
			if(sock[i] == -1) {
				sock[i] = accept(listener, NULL, NULL);
				states[i] = i;
				recv(sock[i], buf, 256, 0);
				printf("Client [%d.] is connected\n", i);
				send(sock[i], hi, 256, 0);
				pthread_create(thr+i, NULL, clientHandler, (void *)(states+i));
				break;
			}
	}

	return 0;
}
void *clientHandler(void *arg) {
	int i = *((int *)arg);
	char buf[200];
	char msg[256];
	sprintf(msg, "[%d] ", i);
	while(1) {
		int ret = recv(sock[i], buf, 200, 0);
		if(ret > 0 && buf[0] != 0) {
			strcat(msg, buf);
			printf("%s\n", msg);

			for(int j = 0; j < NUM_USER; ++j)
				if(sock[j] != -1)
					send(sock[j], msg, 256, 0);//Its worked, return 256.
			sprintf(msg, "[%d] ", i);
			buf[0] = 0;
		}
	}
}