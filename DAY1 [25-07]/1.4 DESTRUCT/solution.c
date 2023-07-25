#include <stdio.h>

struct pkt{
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    int number, generated_number;
    struct pkt pkt;
    printf("Enter an integer\n");
    scanf("%d", &number);

    pkt.ch1 = number&0xff;
    pkt.ch2[0] = (number>>8)&0xff;
    pkt.ch2[1] = (number>>16)&0xff;
    pkt.ch3 = (number>>24)&0xff;

    printf("ch1 : %d\nch2 : [%d, %d]\nch3 : %d\n", pkt.ch1, pkt.ch2[0], pkt.ch2[1], pkt.ch3);

    generated_number = (pkt.ch3<<24) | (pkt.ch2[1]<<16) | (pkt.ch2[0]<<8) | (pkt.ch1);
    printf("Generated number : %d\n", generated_number);

}