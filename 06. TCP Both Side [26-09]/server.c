#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int sock_fd, acpt_fd;
    struct sockaddr_in server_addr, client_addr;
    char msg[100];

    int client_addr_len = sizeof(client_addr);

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock_fd < 0)
    {
        printf("Error creating socket\n");
        return 1;
    }

    printf("Socket Created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5741);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error binding socket\n");
        return 1;
    }

    printf("Done with binding\n");

    if (listen(sock_fd, 5) < 0)
    {
        printf("Error listening\n");
    }

    printf("Listening on 127.0.0.1:5741\n");

    acpt_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (acpt_fd < 0)
    {
        printf("Not Acceptable\n");
        return 1;
    }

    printf("Accepted new client : %s | %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    do
    {
        memset(msg, '\0', sizeof(msg));
        if (recvfrom(acpt_fd, msg, sizeof(msg), 0, (struct sockaddr *)&client_addr, &client_addr_len) < 0)
        {
            printf("Failed to receive message\n");
            return 1;
        }

        printf("Received message : %s\n", msg);

        memset(msg, '\0', sizeof(msg));

        printf("Enter for sending message : ");
        fgets(msg, sizeof(msg), stdin);

        if (sendto(acpt_fd, msg, sizeof(msg), 0, (struct sockaddr *)&client_addr, client_addr_len) < 0)
        {
            printf("Failed to send message\n");
            return 1;
        }
        printf("[Message sent]\n");
    } while (strcmp(msg, "Exit\n"));

    close(sock_fd);
    printf("Socket closed\n");
}