#include <stdio.h>
#include <stdlib.h>

int main(int n, char *arg[]){
    if(n < 2) {
        printf("Insufficient arguments\n");
        return 1;
    }

    int number = atoi(arg[1]), i;
    char *ptr = (char*)&number;

    for(i=0; i<sizeof(number); i++){
        printf("Digit in %dth byte = %d\n",i+1, *ptr);
        ptr++;
    }

    return 0;
}