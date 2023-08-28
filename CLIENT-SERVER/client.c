#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void) {
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_ip[] = "127.0.0.1";
    char client_message[2000], server_message[2000];
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if (socket_desc == -1) {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");
    
    // Set up server address:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    
    // Input for the message:
    printf("Enter a message: ");
    fgets(client_message, sizeof(client_message), stdin);
    
    // Send message to server:
    if (sendto(socket_desc, client_message, strlen(client_message), 0,
         (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        printf("Can't send\n");
        return -1;
    }
    
    // Receive response from server:
    socklen_t server_struct_length = sizeof(server_addr);
    if (recvfrom(socket_desc, server_message, sizeof(server_message), 0,
         (struct sockaddr*)&server_addr, &server_struct_length) == -1) {
        printf("Couldn't receive\n");
        return -1;
    }
    
    printf("Received response from server: %s\n", server_message);
    
    // Close the socket:
    close(socket_desc);
    
    return 0;
}