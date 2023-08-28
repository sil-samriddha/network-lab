#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s <server_address> <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[2]);

    int sock_fd;
    struct sockaddr_in server_addr;
    char msg[100];

    sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(sock_fd < 0) {
        printf("Error creating socket\n");
        return 1;
    }
    printf("Socket created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    printf("[Connected to server %s : %d]\n", argv[1], port);

    do {
        printf("\nEnter message to send : ");
        fgets(msg, sizeof(msg), stdin);

        if (sendto(sock_fd, msg, sizeof(msg), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            printf("Error sending message to server\n");
            break;
        }
        printf("[Message sent]\n");

        if (strcmp(msg, "exit\n") == 0)
            break;

        memset(msg, '\0', sizeof(msg));
        if (recvfrom(sock_fd, msg, sizeof(msg), 0, (struct sockaddr *)&server_addr, &(socklen_t){sizeof(server_addr)}) == -1) {
            printf("Error receiving message from server\n");
            break;
        }

        printf("\nReceived message : %s\n", msg);

    } while (strcmp(msg, "exit\n"));
    
    if(close(sock_fd) == 0)
        printf("Socket closed\n");

}