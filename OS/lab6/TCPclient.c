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
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1337);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int newsock = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	char mess[255] = "I wanna connect!!!!!!!!!!!!!!!!!!!!!!!!!";
	printf("Newsock: %i\n", newsock);
	send(newsock, mess, 20, 0);
	printf("TCPClient sended: %s\n", mess);
	char buf[80] = "";
	recv(newsock, buf, 20, 0);
	printf("TCPClient received from Server: %s\n", buf);
	close(newsock);
	return 0;
}
