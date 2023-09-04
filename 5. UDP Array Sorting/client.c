#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

# define MAX_SIZE 100

typedef struct stack {
    int arr[MAX_SIZE];
    int size;
}ARRAY;

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    int server_addr_len = sizeof(server_addr);

    sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock_fd < 0 ) {
        printf("Error creating socket\n");
        return 1;
    }

    printf("Socket created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5741);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Connected to server : 127.0.0.1 : 5741\n");

    ARRAY arr;
    printf("Enter the size of array : ");
    scanf("%d", &arr.size);

    if(arr.size > MAX_SIZE) {
        printf("Out of memory\n");
        return 1;
    }

    printf("Enter %d elements : \n", arr.size);
    for(int i=0; i<arr.size; i++) {
        scanf("%d", &arr.arr[i]);
    }

    if(sendto(sock_fd, &arr, sizeof(ARRAY), 0, (struct sockaddr *)&server_addr, server_addr_len) < 0){
        printf("Error sending message\n");
        return 1;
    }

    if(recvfrom(sock_fd, &arr, sizeof(ARRAY), 0, (struct sockaddr *)&server_addr, &server_addr_len) < 0){
        printf("Error receiving message\n");
        return 1;
    }

    printf("Sorted array of size %d\n", arr.size);
    for(int i=0; i<arr.size; i++){
        printf("%d ", arr.arr[i]);
    }

    close(sock_fd);
    printf("\nSocket closed\n");

}