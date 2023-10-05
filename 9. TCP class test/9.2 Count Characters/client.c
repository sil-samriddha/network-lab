#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ADDRESS "127.0.0.1"
#define PORT 5741
#define MAX_SIZE 100

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buf[MAX_SIZE];
    int count;
    int server_addr_len = sizeof(server_addr);

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ADDRESS);

    if(connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connecton failure\n");
        return -1;
    }

    printf("Connected to server\n");

    printf("\nEnter string : ");
    fgets(buf, sizeof(buf), stdin);
    

    if(sendto(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, server_addr_len) < 0) {
        printf("Error sending message\n");
        return -1;
    }

    if(recvfrom(sock_fd, &count, sizeof(count), 0, (struct sockaddr *)&server_addr, &server_addr_len) < 0) {
        printf("Error recieving message\n");
        return -1;
    }

    printf("Total no of chars : %d\n", count);
    close(sock_fd);

}