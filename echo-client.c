#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#define MAXLINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <server_port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    char *server_ip = argv[1];
    int server_port = atoi(argv[2]);
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip, &servaddr.sin_addr) <= 0) {
        perror("invalid address / address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connection with the server failed");
        exit(EXIT_FAILURE);
    }

    char buffer[MAXLINE];
    while (1) {
        printf("Enter a message: ");
        if (fgets(buffer, MAXLINE, stdin) == NULL) {
            break;
        }

        send(sockfd, buffer, strlen(buffer), 0);

        ssize_t valread = recv(sockfd, buffer, MAXLINE-1, 0);
        if (valread < 0) {
            perror("recv failed");
            break;
        } else if (valread == 0) {
            puts("Server disconnected");
            break;
        }

        buffer[valread] = '\0';
        printf("Server: %s", buffer);
    }

    close(sockfd);
    return 0;
}