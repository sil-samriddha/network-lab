#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct pack {
    int num1;
    int num2;
} Query_Packet;

int main() {
    int sock_fd, res;
    struct sockaddr_in server_addr, client_addr;
    Query_Packet req;

    sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock_fd < 0) {
        printf("Error creating socket\n");
        return 1;
    }
    printf("Socket created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5741);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int client_addr_len = sizeof(client_addr);

    if(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error binding socket\n");
        return 1;
    }
    printf("Server running on 127.0.0.1\nPort : 5741\n");
    printf("Waiting for client ...\n");

    if(recvfrom(sock_fd, &req, sizeof(Query_Packet), 0, (struct sockaddr *)&client_addr, &client_addr_len) < 0) {
        printf("Error receiving from client\n");
        return 1;
    }

    printf("Request from client port : %i\n", ntohs(client_addr.sin_port));
    printf("Two integers : %d %d\n", req.num1, req.num2);
    res = req.num1 + req.num2;
    printf("%d + %d = %d\n",req.num1, req.num2, res);

    if(sendto(sock_fd, &res, sizeof(res), 0, (struct sockaddr *)&client_addr, client_addr_len) < 0) {
        printf("Error sending to client\n");
        return 1;
    }

    close(sock_fd);
    printf("Socket closed\n");
}