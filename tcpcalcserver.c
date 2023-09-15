#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 22000
#define SA struct sockaddr

void performOperation(int sockfd) {
    int num1, num2, result;
    char operation;

    while (1) {
        // Read two integers and operation choice from the client
        if (read(sockfd, &num1, sizeof(int)) <= 0 || read(sockfd, &num2, sizeof(int)) <= 0 || read(sockfd, &operation, sizeof(char)) <= 0) {
            perror("Read error");
            break;
        }

        switch (operation) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 != 0)
                    result = num1 / num2;
                else
                    result = 0; // Handle division by zero
                break;
            default:
                result = 0; // Invalid operation
        }

        // Send the result back to the client
        write(sockfd, &result, sizeof(int));
    }
}

int main() {
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // Create a socket
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Socket bind failed...\n");
        exit(0);
    } else {
        printf("Socket successfully binded..\n");
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) != 0) {
        printf("Listen failed...\n");
        exit(0);
    } else {
        printf("Server listening..\n");
    }

    socklen_t len = sizeof(cli);

    while (1) {
        // Accept the data packet from the client
        connfd = accept(sockfd, (SA*)&cli, &len);
        if (connfd < 0) {
            printf("Server accept failed...\n");
            exit(0);
        } else {
            printf("Server accepted the client...\n");
            // Function for handling client requests
            performOperation(connfd);
            // Close the connection with the client
            close(connfd);
        }
    }

    // Close the server socket
    close(sockfd);

    return 0;
}
