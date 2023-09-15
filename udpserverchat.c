#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char str[100];
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(22000);
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Server is ready to receive messages.\n");
    while (true) {
        recvfrom(sockfd, str, sizeof(str), 0, (struct sockaddr *)&cliaddr, &len);
        printf("Client: %s", str);
        if (strcmp(str, "exit\n") == 0) {
            printf("Chat ended by client.\n");
            break;
        }
        printf("Server: ");
        fgets(str, sizeof(str), stdin);  // Read server's response
        sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        if (strcmp(str, "exit\n") == 0) {
            printf("Chat ended by server.\n");
            break;
        }
    }
    close(sockfd);
    return 0;
}