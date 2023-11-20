#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define ADDRESS "127.0.0.1"
#define PORT 5741
#define MAX_SIZE 1024

int main () {
    int sock_fd, accpt_fd;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    char message[MAX_SIZE];

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock_fd < 0) {
        printf("Error creating socket\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ADDRESS);

    if (bind(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        printf("Error binding socket\n");
        return -1;
    }

    if (listen(sock_fd, 5) < 0) {
        printf("Error listening on socket\n");
        return -1;
    }

    accpt_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &client_addr_len);

    if (accpt_fd < 0) {
        printf("Error accepting connection\n");
        return -1;
    }

    printf("Connected to client at %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    while (1) {
        memset(message, '\0', sizeof(message));
        if (recvfrom(accpt_fd, message, sizeof(message), 0, (struct sockaddr *) &client_addr, &client_addr_len) < 0) {
            printf("Error receiving message\n");
            return -1;
        }

        printf("Received message: %s\n", message);

        if (strcmp(message, "exit\n") == 0) break;

        printf("Enter anything to send to client: ");
        fgets(message, sizeof(message), stdin);

        if (sendto (accpt_fd, message, strlen(message), 0, (struct sockaddr *) &client_addr, client_addr_len) < 0) {
            printf("Error sending message\n");
            return -1;
        }
        printf("[Message Sent]\n");
    }

    close(sock_fd);

}