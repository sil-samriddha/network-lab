#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

# define SERVER_ADDR "127.0.0.1"
# define SERVER_PORT 5741

struct person {
    int id;
    char name[30];
    int age;
    int height;
    int weight;
};

int main() {
    int sock_fd, query;
    struct sockaddr_in server_addr;
    int server_addr_len = sizeof(server_addr);

    struct person p;

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0) {
        printf("Error creating socket\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error connecting to server\n");
        return -1;
    }

    printf("Connected to server\n");

    printf("Enter user id : ");
    scanf("%d", &query);

    if(sendto(sock_fd, &query, sizeof(query), 0, (struct sockaddr *)&server_addr, server_addr_len) < 0) {
        printf("Error sending to server\n");
        return -1;
    }

    if(recvfrom(sock_fd, &p, sizeof(struct person), 0, (struct sockaddr *)&server_addr, &server_addr_len) < 0) {
        printf("Error recieving from server\n");
        return -1;
    }

    if(p.id == -1){
        printf("User not found\n");
    }else{
        printf("Displaying information\n");
        printf("Name \t: %s\n"
        "Age \t: %d\n"
        "Height \t: %d\n"
        "Weight \t: %d\n", p.name, p.age, p.height, p.weight);
    }

    close(sock_fd);
    printf("Socket closed\n");
}