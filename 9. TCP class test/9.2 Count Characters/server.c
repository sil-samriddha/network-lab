#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define ADDRESS "127.0.0.1"
#define PORT 5741
#define MAX_SIZE 100

int count_char(char buf[]){
    int count = 0;
    for(int i=0; buf[i]!='\0'; i++){
        count++;
    }
    return count-1;
}

int main(){
    int sock_fd, acpt_fd;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    char buf[MAX_SIZE];

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0){
        printf("Socket creation failed\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ADDRESS);

    if(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Binding failed\n");
        return -1;
    }

    if(listen(sock_fd, 5) < 0) {
        printf("Listening failed\n");
    }
    printf("Server listening on port %d\n", PORT);

    acpt_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if(acpt_fd < 0) {
        printf("Client failed to accept\n");
        return -1;
    }

    printf("\nClient connected : %s port: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    if(recvfrom(acpt_fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &client_addr_len) < 0) {
        printf("Failed to receive\n");
        return -1;
    }

    printf("Received string : %s", buf);

    int count = count_char(buf);
    printf("Char count : %d\n", count);

    if(sendto(acpt_fd, &count, sizeof(count), 0,(struct sockaddr *)&client_addr, client_addr_len) < 0){
        printf("Failed to send\n");
        return -1;
    }
    printf("Sent\n");

    close(sock_fd);
}