#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main()
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr, client;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1337);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	unsigned int cllen = sizeof(client);
	char buf[80];
	recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&client, &cllen);
	printf("UDPServer received from Client: %s\n", buf);
	char mess[] = "You are connected!";
	sendto(sock, mess, sizeof(mess), 0, (struct sockaddr*)&client, cllen);
	printf("UDPServer sended: %s\n", mess);
	return 0;
}
