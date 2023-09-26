#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sock_fd;
    struct sockaddr_in server_addr;
    char msg[100];

    int server_addr_len = sizeof(server_addr);

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock_fd < 0)
    {
        printf("Error creating socket\n");
        return 1;
    }

    printf("Socket created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5741);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error connecting to server\n");
        return 1;
    }

    printf("Connected to server\n");

    do
    {
        memset(msg, '\0', sizeof(msg));
        printf("Enter message for sending ['Exit' to close] : ");
        fgets(msg, sizeof(msg), stdin);

        if (strcmp(msg, "Exit\n") == 0)
        {
            break;
        }

        if (sendto(sock_fd, msg, sizeof(msg), 0, (struct sockaddr *)&server_addr, server_addr_len) < 0)
        {
            printf("Error sending to server\n");
            return 1;
        }
        printf("[Message Sent]\n");

        if (recvfrom(sock_fd, msg, sizeof(msg), 0, (struct sockaddr *)&server_addr, &server_addr_len) < 0)
        {
            printf("Error recieving from server\n");
            return 1;
        }
        printf("Received from server : %s\n", msg);
    } while (strcmp(msg, "Exit\n"));

    close(sock_fd);
    printf("Socket closed\n");
}