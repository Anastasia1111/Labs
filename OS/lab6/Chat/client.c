#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
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
	system("clear");
	int sock;
	char ip[20];
	struct sockaddr_in addr;
	pthread_t thr;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1337);
	
	printf("IP to connect: ");
	scanf("%s", ip);
	
	addr.sin_addr.s_addr = inet_addr(ip);
	
	printf("Starting...\n");
	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	
	char msg[256] = "Connecting...";
	printf("%s", msg);
	if(send(sock, msg, 256, 0) > 0);
		printf("Connected.\n");
	pthread_create(&thr, NULL, messRecv, &sock);
	
	int i = 0;
	while(1) {
		scanf("%s", msg);
		send(sock, msg, 256, 0);
	}
	close(sock);
	return 0;
}

void *messRecv(void *arg) {
	int sock = *((int *)arg);
	char buf[256];
	while(1) {
		if(recv(sock, buf, 256, 0) > 0)
		{
			printf("%s\n", buf);
		}
	}
}
