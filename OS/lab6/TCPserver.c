#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr, client;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1337);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	listen(sock, 1);
	unsigned int cllen = sizeof(client);
	int newsock = accept(sock, (struct sockaddr*)&client, &cllen);
	printf("Newsock: %i\n", newsock);
	char buf[80] = "";
	recv(newsock, buf, 20, 0);
	printf("TCPServer received from Client: %s\n", buf);
	char mess[255] = "You are connected!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	send(newsock, mess, 20, 0);
	printf("TCPServer sended: %s\n", mess);
	close(newsock);
	return 0;
}
