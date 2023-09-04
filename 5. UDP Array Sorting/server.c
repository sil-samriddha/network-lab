#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

# define MAX_SIZE 100

typedef struct stack {
    int arr[MAX_SIZE];
    int size;
}ARRAY;

void sort(ARRAY *arr){
    for(int i = 1; i < arr->size; i++) {
        int curr = arr->arr[i];
        int j = i -1;

        while(j>=0 && arr->arr[j] > curr) {
            arr->arr[j + 1] = arr->arr[j];
            j--;
        }
        arr->arr[j+1] = curr;
    }
}

int main () {
    int sock_fd;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    sock_fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock_fd < 0) {
        printf("Error creating socket\n");
        return 1;
    }
    printf("Socket created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5741);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr))<0){
        printf("Error while binding\n");
        return 1;
    }
    
    printf("Server running on port 5741\nIPv4 : 127.0.0.1\n");

    ARRAY arr;
    if(recvfrom(sock_fd, &arr, sizeof(ARRAY), 0, (struct sockaddr *)&client_addr, &client_addr_len) < 0){
        printf("Error receiving message\n");
        return 1;
    }

    sort(&arr);

    if(sendto(sock_fd, &arr, sizeof(ARRAY), 0, (struct sockaddr *)&client_addr, client_addr_len) < 0){
        printf("Error sending message\n");
        return 1;
    }

    close(sock_fd);
    printf("Socket closed\n");
}