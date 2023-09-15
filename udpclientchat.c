#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int main(int argc, char **argv) {
    int sockfd;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("Connected to the server. Start chatting (type 'exit' to end).\n");
    while (true) {
        printf("Client: ");
        fgets(sendline, sizeof(sendline), stdin);  // Read client's message
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, len);
        if (strcmp(sendline, "exit\n") == 0) {
            printf("Chat ended by client.\n");
            break;
        }
        recvfrom(sockfd, recvline, sizeof(recvline), 0, (struct sockaddr *)&servaddr, &len);
        printf("Server: %s", recvline);
        if (strcmp(recvline, "exit\n") == 0) {
            printf("Chat ended by server.\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}