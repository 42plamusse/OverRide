#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char buffer[0];

    fgets(buffer, 0x68, stdin);
    for (int i = 0; i < strlen(buffer); i++)
        buffer[i] = tolower(buffer[i]);

    printf(buffer);
}