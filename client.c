#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<string.h>

int main()
{
	int sockfd;
	struct sockaddr_in serveraddr;
	char sendline[100], recvline[100];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(2200); 

	connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	fgets(sendline, 100, stdin);  
        bzero(recvline,100);
	send(sockfd, sendline, strlen(sendline), 0);
	recv(sockfd, recvline, 100, 0);
	printf("echo back by server: %s", recvline);
	return 0;
}
