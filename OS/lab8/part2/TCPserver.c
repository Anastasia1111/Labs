#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int sock, listener;
	struct sockaddr_in addr, client;
	char buf[256];
	
	listener = socket(AF_INET, SOCK_STREAM, 0);
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(listener, (struct sockaddr *)&addr, sizeof(addr));
	
	listen(listener, 1);
	
	sock = accept(listener, NULL, NULL);
	
	recv(sock, buf, 256, 0);
	
	char msg[256] = "HTTP /1.0 200 ok\n\n";
	send(sock, msg, 256, 0);
	
	close(sock);
	return 0;
}
