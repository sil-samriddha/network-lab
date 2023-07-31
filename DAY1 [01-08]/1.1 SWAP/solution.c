#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void swap(int *a, int *b){
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int is_number(char* arg) {
    while (*arg) {
        if (!isdigit(*arg)) {
            return 0;
        }
        arg++;
    }
    return 1;
}

int main(int argc, char *argv[]){
    if (argc < 3) {
        printf("Insufficient arguments\n");
        return 1;
    }
    if (!is_number(argv[1]) || !is_number(argv[2])) {
        printf("Two arguments should be two numbers\n");
        return 1;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    swap(&a, &b);
    printf("After swapping\n%d %d\n", a, b);
}