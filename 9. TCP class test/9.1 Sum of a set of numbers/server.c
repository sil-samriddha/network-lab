#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

# define PORT 5741
# define ADDRESS "127.0.0.1"
# define MAX_SIZE 100

long sum_of_nums (int arr[]){
    long ans = 0;
    for(int i=0; arr[i]!= 0; i++){
        printf("%d ", arr[i]);
        ans += arr[i];
    }
    return ans;
}

int main () {
    int sock_fd, acpt_fd;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    int arr[MAX_SIZE];

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0) {
        printf("Error creating socket\n");
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
        printf("Error listening\n");
        return -1;
    }

    printf("Server listening on port %d\n", PORT);

    acpt_fd =  accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    if(acpt_fd < 0) {
        printf("Error accepting client\n");
        return -1;
    }

    printf("Client connected %s port : %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    if(recvfrom(acpt_fd, &arr, sizeof(arr), 0, (struct sockaddr *)&client_addr, &client_addr_len) < 0){
        printf("Error receiving from client\n");
        return -1;
    }

    long sum = sum_of_nums(arr);

    printf("\nSum : %ld\n", sum);
    if(sendto(acpt_fd, &sum, sizeof(sum), 0, (struct sockaddr *)&client_addr, client_addr_len) < 0) {
        printf("Error sending to client\n");
        return -1;
    }
    printf("Sent\n");

    close(sock_fd);

}