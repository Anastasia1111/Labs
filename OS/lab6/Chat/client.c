#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *messRecv(void *arg);

int main()
{
	printf("Starting...\n");
	int sock;
	struct sockaddr_in addr;
	pthread_t thr;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1337);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	
	char msg[256] = "Connecting...";
	printf("%s", msg);
	send(sock, msg, 256, 0);
	printf("Connected.\n");
	pthread_create(&thr, NULL, messRecv, &sock);

	while(1) {
		scanf("%s", msg);
		send(sock, msg, 256, 0);
	}
	close(sock);
	return 0;
}

void *messRecv(void *arg) {
	int bsock = *((int *)arg);
	char buf[256];
	while(1) {
		if(recv(bsock, buf, 256, 0) >= 0)
			printf("%s\n", buf);
	}
}
