#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

# define ADDRESS "127.0.0.1"
# define PORT 5741
# define MAX_CONTENT 1024

int main() {
    int sock_fd;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock_fd < 0) {
        printf("Error creating socket\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ADDRESS);

    if(bind(sock_fd, (struct sockaddr *)&server_addr, client_addr_len) < 0) {
        printf("Error binding socket\n");
        return -1;
    }

    printf("Binding successfull\n");
    printf("Running on 127.0.0.1:5741\n");

    char fileName[50];
    char fileContent[MAX_CONTENT];

    if(recvfrom(sock_fd, fileName, sizeof(fileName), 0, (struct sockaddr *)&client_addr, &client_addr_len) < 0) {
        printf("Error receiving file name\n");
        return -1;
    }

    printf("Requested file name : %s\n", fileName);
    printf("[From IP : %s, Port: %d]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    FILE *file;
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    fgets(fileContent, sizeof(fileContent), file);


    if (sendto(sock_fd, fileContent, sizeof(fileContent), 0, (struct sockaddr *)&client_addr, client_addr_len) < 0) {
        printf("Error sending file\n");
        return -1;
    }

    close(sock_fd);
}