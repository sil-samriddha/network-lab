#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ADDRESS "127.0.0.1"
#define PORT 5741

struct packet {
    int num1, num2;
    long result;
    char operator;
};


int main () {
    int sock_fd;
    struct sockaddr_in server_addr;
    int server_addr_len = sizeof(server_addr);

    struct packet p;

    sock_fd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0) {
        printf("Error creating socket\n");
        return -1;
    }
    printf("Socket created\n");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons (PORT);
    server_addr.sin_addr.s_addr = inet_addr(ADDRESS);

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error connecting to server\n");
        return -1;
    }

    printf("Connected to server\n");

    printf("Choose any operator : \n+  Addition\n-  Substitution\n*  Multiplication\n/  Division\n");

    printf("Operator : ", p.operator);
    scanf("%c", &p.operator);
    printf("Number 1 : ");
    scanf("%d", &p.num1);
    printf("Number 2 : ");
    scanf("%d", &p.num2);

    if(sendto(sock_fd, &p, sizeof(p), 0, (struct sockaddr *)&server_addr, server_addr_len) < 0){
        printf("Error sending message\n");
        return -1;
    }

    if(recvfrom(sock_fd, &p, sizeof(p), 0, (struct sockaddr *)&server_addr, &server_addr_len) < 0) {
        printf("Error receiving form server\n");
        return -1;
    }

    if(p.operator == '\0'){
        printf("Operation not supported\n");
    }else{
        printf("%d %c %d = %lu\n", p.num1, p.operator, p.num2, p.result);
    }

    close(sock_fd);
    printf("Socket closed\n");
}