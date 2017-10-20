#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main()
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1337);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	char mess[] = "I connect to server!";
	unsigned int addrln = sizeof(addr);
	sendto(sock, mess, sizeof(mess), 0, (struct sockaddr*)&addr, addrln);
	printf("UDPClient sended: %s\n", mess);
	char buf[80];
	recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &addrln);
	printf("UDPClient received from Server: %s\n", buf);
	return 0;
}

