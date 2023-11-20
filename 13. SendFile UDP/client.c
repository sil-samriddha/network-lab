#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 5741
#define MAX_SIZE 1024

int main(){
    int sock_fd;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);

    sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock_fd < 0) {
        printf("Error creating socket");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    printf("Connecting to server\n");


    char fileName[50];
    char fileContent[MAX_SIZE];
    printf("\nEnter the file name with extension requested : \n");
    scanf("%s", fileName);

    if (sendto(sock_fd, fileName, sizeof(fileName), 0, (struct sockaddr *)&addr, addrlen) < 0) {
        printf("Error sending to server\n");
        return -1;
    }

    printf("Request sent to the server\n");

    memset(fileContent, '\0', sizeof(fileContent));
    if (recvfrom(sock_fd, fileContent, sizeof(fileContent), 0, (struct sockaddr *)&addr, &addrlen) < 0) {
        printf("Error receiving from server\n");
        return -1;
    }

    printf("Received file content successfully\n");

    FILE *file = fopen("Received.txt", "w");
    if (file == NULL) {
        printf("Error creating file\n");
        return -1;
    }

    fputs(fileContent, file);

    printf("File created successfully\n");

    close(sock_fd);   
}