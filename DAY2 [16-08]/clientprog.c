#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sock_fd, status, port = 5741;
    struct sockaddr_in addr;
    char message[50];

    memset(message, '\0', sizeof(message));

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock_fd < 0) {
        printf("Error creating socket\n");
        return 1;
    }else{
        printf("Socket created\n");
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    status = bind(sock_fd, (struct sockaddr_in *)&addr, sizeof(struct sockaddr_in));

    if(status < 0) {
        printf("Error binding socket\n");
        return 1;
    }else{
        printf("Listing on port %d\n", port);
    }

    do {
        status = recvfrom(sock_fd, (void *) message, sizeof(message), 0, (struct sockaddr_in *) &addr, sizeof(struct sockaddr_in));
        if(status == 0) {
            printf("Error getting message\n");
            return 1;
        }else {
            printf("Received message : %s", message);
        }
    } while(strcmp(message , "exit\n"));

    status = close(sock_fd);
    if(status == 0) {
        printf("Socket closed\n");
    } 
    return 0;
}