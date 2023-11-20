#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ADDRESS "127.0.0.1"
#define PORT 5741

struct packet {
    int num1, num2;
    long result;
    char operator;
};

void calculate(struct packet* pack){
    if(pack->operator == '+'){
        pack->result = pack->num1 + pack->num2;
    }else if(pack->operator== '-'){
        pack->result = pack->num1 - pack->num2;
    }else if(pack->operator == '*'){
        pack->result = pack->num1 * pack->num2;
    }else if(pack->operator == '/'){
        pack->result = pack->num1 / pack->num2;
    }else{
        pack->operator = '\0';
    }
}

int main () {
    int sock_fd, acpt_fd;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    struct packet p;

    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0){
        printf("Error creating socket\n");
        return -1;
    }
    printf("Socket Created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ADDRESS);

    if(bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("Error binding socket\n");
        return -1;
    }

    printf("Done with binding\n");

    if(listen(sock_fd, 5 ) < 0) {
        printf("Error listening\n");
        return -1;
    }

    printf("Listening on %s port %d\n", ADDRESS, PORT);

    acpt_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (acpt_fd < 0) {
        printf("Not Acceptable\n");
        return -1;
    }

    printf("CLient conected : %s Port : %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    if(recvfrom(acpt_fd, &p, sizeof(p), 0, (struct sockaddr *)&client_addr, &client_addr_len) < 0) {
        printf("Error receiving message\n");
        return -1;
    }

    printf("Request processing for\n %d %c %d\n", p.num1, p.operator, p.num2);
    calculate(&p);
    if(p.operator == '\0'){
        printf("Operation not supported\n");
    }else{
        printf("Result = %d\n",p.result);
    }

    if(sendto(acpt_fd, &p, sizeof(p), 0, (struct sockaddr*)&client_addr, client_addr_len) < 0){
        printf("Error sending message\n");
        return -1;
    }

    close(sock_fd);
    printf("Socket closed\n");
}

