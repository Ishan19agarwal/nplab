#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 22000
#define SA struct sockaddr

void performOperation(int sockfd) {
    int num1, num2, result;
    char operation;

    for (;;) {
        printf("Enter two integers and operation (e.g., 5 3 +): ");
        scanf("%d %d %c", &num1, &num2, &operation);

        // Send the two integers and operation to the server
        write(sockfd, &num1, sizeof(int));
        write(sockfd, &num2, sizeof(int));
        write(sockfd, &operation, sizeof(char));

        // Read the result from the server
        if (read(sockfd, &result, sizeof(int)) <= 0) {
            perror("Read error");
            break;
        }

        printf("Result from Server: %d\n", result);
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    // Socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    } else {
        printf("Socket successfully created..\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    // Assign IP and PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the server's IP address
    servaddr.sin_port = htons(PORT);

    // Connect the client socket to the server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection with the server failed...\n");
        exit(0);
    } else {
        printf("Connected to the server..\n");
    }

    // Function for performing calculations with the server
    performOperation(sockfd);

    // Close the socket
    close(sockfd);

    return 0;
}
