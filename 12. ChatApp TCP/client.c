#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 5741
#define MAX_SIZE 1024

int main () {
    int sock_fd;
    struct sockaddr_in addr;
    int addr_len = sizeof(addr);

    char message[MAX_SIZE];

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock_fd < 0) {
        printf("Error creating socket\n");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    if (connect (sock_fd, (struct sockaddr *)&addr, addr_len) < 0) {
        printf("Error connecting to server\n");
        return -1;
    }

    printf("Connection established\n");

    while (1) {
        memset(message, '\0', sizeof(message));
        printf("Enter message to send : ");
        fgets(message, sizeof(message), stdin);

        if (sendto(sock_fd, message, sizeof(message), 0, (struct sockaddr *)&addr, addr_len) < 0) {
            printf("Error sending to server\n");
            return -1;
        }

        printf("[Message Sent]\n");

        if (recvfrom(sock_fd, message, sizeof(message), 0, (struct sockaddr *)&addr, &addr_len) < 0) {
            printf("Error receiving from server\n");
            return -1;
        }

        printf("Received message: %s\n", message);
        if (strcmp(message, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }
    }

    close(sock_fd);

}