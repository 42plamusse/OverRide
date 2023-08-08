#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void decrypt(int n)
{
    char str[] = "Q}|u`sfg~sf{}|a3"; // 0xffffd68b
    char c;
    int len;
    int i;

    len = strlen(str);
    i = 0;
    while (i < len)
        str[i] = str[i++] ^ n;

    if (!(strncmp(str, "Congratulations!", 0x11)))
        system("/bin/sh");
    else
        puts("Invalid password!\n");
}

void test(int n1, int n2)
{
    int diff;

    diff = n2 - n1;
    if (diff <= 0x15)
        decrypt(diff);
    else
        decrypt(rand());
}

int main(void)
{
    int n;

    srand((unsigned)time(0));
    scanf("%d", n);
    test(n, 0x1337d00d);
}