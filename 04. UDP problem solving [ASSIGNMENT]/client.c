#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct pack {
    int num1;
    int num2;
} Query_Packet;

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    Query_Packet req;
    int res;

    sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock_fd < 0){
        printf("Error creating socket");
        return 1;
    }

    printf("Socket created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5741);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int addr_len = sizeof(server_addr);

    printf("Connecting to server : 127.0.0.1 : 5741\n");

    printf("\nEnter two integer numbers :\n");
    scanf("%d %d", &req.num1, &req.num2);

    if(sendto(sock_fd, (Query_Packet *)&req, sizeof(req), 0, (struct sockaddr *)&server_addr, addr_len) < 0){
        printf("Error sending to server\n");
        return 1;
    }

    printf("\nRequest send to the server\nWaiting for response from server...\n");

    if(recvfrom(sock_fd, &res, sizeof(res), 0, (struct sockaddr *)&server_addr, &addr_len) < 0){
        printf("Error receiving response from server\n");
        return 1;
    }

    printf("\nAddition of two numbers : %d\n", res);

    close(sock_fd);
    printf("Socket closed\n");
}