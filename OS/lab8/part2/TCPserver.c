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
	
	listen(listener, 3);
	socklen_t l = sizeof(struct sockaddr_in);
	sock = accept(listener, (struct sockaddr *)&client, (socklen_t *)&l);
	
	recv(sock, buf, 256, 0);
	
	char msg[256] = "HTTP/1.0 200 OK\r\n\r\n"
	"<html> \r\n"
	"<head> \r\n"
		"Hi \r\n"
	"</head> \r\n"
	"<body> \r\n"
		"Hello everyone!!! \r\n"
	"</body> \r\n"
	"</html> \r\n";

	send(sock, msg, 256, 0);
	recv(sock, buf, 256, 0);
	
	// printf("%s", buf);
	close(sock);
	return 0;
}
