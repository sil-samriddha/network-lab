#include <stdio.h>

void swap(int *a, int *b){
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main(){
    int a, b;
    printf("Enter two integers\n");
    scanf("%d %d", &a, &b);

    swap(&a, &b);
    printf("After swapping two integers\n%d %d\n", a, b);
}