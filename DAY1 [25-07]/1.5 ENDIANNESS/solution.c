#include <stdio.h>

int main () {
    int number, i, lsb, converted_number;
    char *ptr = (char *)&number;
    printf("Enter any integer\n");
    scanf("%d", &number);

    lsb = number & 0xff;
    printf("\nLSB of %d is : %d", number, lsb);

    printf("\n-----------------------");
    printf("\nMemory Address\tValue\n");
    printf("-----------------------\n");
    for(i = 0; i < 4; i ++) {
        printf("%p\t", ptr);
        printf("%d\n", *ptr++);
    }
    printf("-----------------------\n");

    converted_number = (*(--ptr)) 
                       | (*(--ptr)<<8) 
                       | (*(--ptr)<<16) 
                       | (*(--ptr)<<24);

    if(lsb == *(ptr)){
        printf("The LSB of the number is stored at the lowest memory address\n"
               "Hence the host machine is LITTLE ENDIAN.\n");
        printf("Big endian format of the number : %d\n", converted_number);
    }else {
        printf("The LSB of the number is stored at the highest memory address\n"
               "Hence the host machine is BIG ENDIAN.\n");
        printf("Little endian format of the number : %d\n", converted_number);
    }
}