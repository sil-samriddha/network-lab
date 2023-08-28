#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sock_fd;
    struct sockaddr_in server_addr, client_addr;
    char msg[100];

    char address[] = "127.0.0.1";
    int port = 5741;
    int client_addr_len = sizeof(client_addr);

    sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock_fd < 0) {
        printf("Error creating socket\n");
        return 1;
    }
    printf("Socket created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(address);

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error while binding\n");
        return 1;
    }

    printf("IPv4 address :\t%s\nPort no :\t%d\n", address, port);

    do {
        memset(msg, '\0', sizeof(msg));
        printf("\nWaiting for client...\n");
        if (recvfrom(sock_fd, msg, sizeof(msg), 0, (struct sockaddr *)&client_addr, &client_addr_len) == -1) {
            printf("Error receiving message from client\n");
            break;
        }

        printf("\nReceived message : %s"
               "[ Client Address : %s ] [ Port : %d ]\n",
               msg, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        printf("Sending message : ");

        fflush(stdin);
        memset(msg, '\0', sizeof(msg));
        fgets(msg, sizeof(msg), stdin);

        if (sendto(sock_fd, msg, sizeof(msg), 0, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
            printf("Error sending message\n");
            break;
        }

    } while (strcmp(msg, "exit\n"));

    if (close(sock_fd) == 0) {
        printf("Socket closed\n");
    }
}