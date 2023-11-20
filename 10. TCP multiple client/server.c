#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_LENGTH 100
#define ADDRESS "127.0.0.1"
#define PORT 5741
#define MAX_CLIENT 5

int main()
{
    int sock_fd, acpt_fd[MAX_CLIENT];
    struct sockaddr_in server_addr, client_addr;
    char msg[MAX_LENGTH];

    int client_addr_len = sizeof(client_addr);

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock_fd < 0)
    {
        printf("Error creating socket\n");
        return -1;
    }

    printf("Socket Created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ADDRESS);

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error binding socket\n");
        return -1;
    }

    printf("Done with binding\n");

    if (listen(sock_fd, 5) < 0)
    {
        printf("Error listening\n");
    }

    printf("Listening on %s:%d\n", ADDRESS, PORT);

    for (int i = 0; i < MAX_CLIENT; i++)
    {
        acpt_fd[i] = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);

        if (acpt_fd[i] < 0)
        {
            printf("Not Acceptable\n");
            return -1;
        }

        printf("Accepted new client %d: %s:%d\n", i, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        memset(msg, '\0', sizeof(msg));
        if (recvfrom(acpt_fd[i], msg, sizeof(msg), 0, (struct sockaddr *)&client_addr, &client_addr_len) < 0)
        {
            printf("Failed to receive message\n");
            return -1;
        }

        printf("Received message from client %d: %s\n", i, msg);

        memset(msg, '\0', sizeof(msg));

        printf("Enter message for sending to client %d: ", i);
        fgets(msg, sizeof(msg), stdin);

        if (sendto(acpt_fd[i], msg, sizeof(msg), 0, (struct sockaddr *)&client_addr, client_addr_len) < 0)
        {
            printf("Failed to send message\n");
            return 1;
        }
        printf("[Message sent]\n");
    }

    close(sock_fd);
    printf("Socket closed\n");
}
