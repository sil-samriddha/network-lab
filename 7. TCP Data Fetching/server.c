#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

# define MAX_CAPACITY 10
# define SERVER_ADDRESS "127.0.0.1"
# define SERVER_PORT 5741

struct person {
    int id;
    char name[30];
    int age;
    int height;
    int weight;
};

struct person not_found = {-1, "", -1, -1, -1};

struct person* search (struct person *p, int st, int ed, int user_id) {
    int mid = st + (ed-st)/2;
    while(st <= ed) {
        if((p+mid)->id == user_id){
            return p+mid;
        }
        if((p+mid)->id > user_id){
            ed = mid-1;
        }else{
            st = mid+1;
        }
        mid = st + (ed-st)/2;
    }
    
    return &not_found;
}

int main() {
    int sock_fd, acpt_fd, req_id;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0) {
        printf("Error creating socket\n");
        return -1;
    }

    printf("Socket created\n");

    FILE *file;
    file = fopen("data.csv", "r");
    if (file == NULL) {
        printf("Error opening data file\n");
        return 1;
    }

    struct person *p;
    p = (struct person *)malloc(MAX_CAPACITY * sizeof(struct person));
    if (p == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }
    printf("Memory Allocated : %d bytes \n", MAX_CAPACITY*sizeof(struct person));

    int count = 0, choice;
    char line[50];
    
    while ((line[0] = fgetc(file)) != '\n' && line[0] != EOF);

    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, ",");
        p[count].id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(p[count].name, token);

        token = strtok(NULL, ",");
        p[count].age = atoi(token);

        token = strtok(NULL, ",");
        p[count].height = atoi(token);

        token = strtok(NULL, ",");
        p[count].weight = atoi(token);

        count++;

        if (count >= MAX_CAPACITY) {
            printf("Out of memory\n");
            return -1;
        }
    }

    printf("Data fetched \t : %d items \n", count);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    if(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("Error binding socket\n");
        return -1;
    }

    if (listen(sock_fd, 5) < 0) {
        printf("Error listening\n");
        return -1;
    }

    printf("Listening on : %s | Port : %d\n", SERVER_ADDRESS, SERVER_PORT);

    acpt_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (acpt_fd < 0) {
        printf("Not Acceptable\n");
        return -1;
    }
    printf("New Client : %s | Port : %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    if(recvfrom(acpt_fd, &req_id, sizeof(req_id), 0, (struct sockaddr *)&client_addr, &client_addr_len) < 0) {
        printf("Error receiving message\n");
        return -1;
    }

    if(sendto(acpt_fd, search(p, 0, count-1, req_id), sizeof(struct person), 0, (struct sockaddr *)&client_addr, client_addr_len) < 0) {
        printf("Error sending message\n");
        return -1;
    }

    close(sock_fd);
    printf("Socket closed\n");
}