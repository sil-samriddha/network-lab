#include <stdio.h>

int main(){
    int number, i;
    char *ptr = (char*)&number;

    printf("Enter an integer\n");
    scanf("%d",&number);

    for(i=0; i<sizeof(number); i++){
        printf("%d ",*ptr);
        ptr++;
    }

}