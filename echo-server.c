#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>


#define DEFAULT_PORT 5000
int port = DEFAULT_PORT;
#define MAXLINE 1024

void *handle_client(void *arg) {
    int valread;
    int new_socket = *((int *)arg);
    free(arg);
    char buffer[MAXLINE];
    ssize_t valsend;

    while ((valread = recv(new_socket, buffer, MAXLINE-1, 0)) > 0) {
        buffer[valread] = '\0';
        printf("%s\n", buffer);
        send(new_socket, buffer, valread, 0);
    }

    if (valread == 0) {
        puts("Client disconnected");
    } else {
        perror("recv failed");
    }

    close(new_socket);
    return NULL;
}

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p':
                port = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    int sockfd;
    int server_sock;
    int client_sock;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((client_sock = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) < 0) {
            perror("accept failed");
            continue;
        }

        pthread_t tid;
        int *new_socket = malloc(sizeof(int));
        *new_socket = client_sock;

        if (pthread_create(&tid, NULL, handle_client, new_socket) != 0) {
            perror("pthread_create failed");
            free(new_socket);
            close(client_sock);
        } else {
            pthread_detach(tid);
        }
    }

    close(sockfd);
    return 0;

}
