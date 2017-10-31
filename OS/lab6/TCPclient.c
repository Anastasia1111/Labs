#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int sock;
	struct sockaddr_in addr;
	char buf[80];
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1337);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	
	char msg[256] = "I wanna connect!";
	send(sock, msg, 256, 0);
	printf("TCPClient sended: %s\n", msg);
	
	recv(sock, buf, 256, 0);
	printf("TCPClient received from Server: %s\n", buf);
	
	close(sock);
	return 0;
}
