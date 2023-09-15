#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int comm_sock, comm_fd;
	char str[100];
	int sockid = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serveraddr, cliaddr;
    bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  
	serveraddr.sin_port = htons(2200);

	bind(sockid, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	listen(sockid,10);

	while(1) 
	{
	comm_sock = accept(sockid, (struct sockaddr*)NULL,NULL);
	recv(comm_sock, str, 100, 0);
	printf("received - %s",str);

	send(comm_sock,str,strlen(str),0); 
	close(comm_sock);
	}


}
