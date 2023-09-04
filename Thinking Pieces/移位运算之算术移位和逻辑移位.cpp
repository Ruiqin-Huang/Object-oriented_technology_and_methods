#include <stdio.h>

void printBinary(unsigned char data) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (data >> i) & 1);
    }
    printf("\n");
}

int main() {
    unsigned char binaryData = 0b11011010;  // 二进制表示为: 11011010

    printf("Original Binary representation: ");
    printBinary(binaryData);

    unsigned char shiftedData = binaryData >> 4;

    printf("Shifted Binary representation: ");
    printBinary(shiftedData);

    return 0;
}
