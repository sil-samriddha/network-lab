#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sock_fd, status, port = 5741;
    struct sockaddr_in addr;
    char message[50];
    char host_addr[] = "127.0.0.1";

    memset(message, '\0', sizeof(message));

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock_fd < 0) {
        printf("Error creating socket\n");
        return 1;
    }else{
        printf("Socket created\n");
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(host_addr);

    do {
        printf("Enter message to send ['exit' to close] : ");
        fgets(message, 50, stdin);

        status = sendto(sock_fd, (void *)message, sizeof(message), 0, (struct sockaddr_in *)&addr, sizeof(struct sockaddr_in));

        if(status < 0) {
            printf("Error sending message\n");
            return 1;
        }
        
    } while (strcmp(message, "exit\n"));

    status = close(sock_fd);
    if(status == 0) {
        printf("Socket closed\n");
    }

    return 0;
}