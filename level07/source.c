#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void clear_stdin(void)
{
    int tmp;

    tmp = getchar();
    while ((char)tmp != -1)
    {
        if ((char)tmp == '\n')
            return;
    }
}

unsigned int get_unum(void)
{
    unsigned int result = 0;

    fflush(stdout);
    scanf("%u", &result);
    clear_stdin();
    return result;
}

int store_number(char *buff)
{
    unsigned int n = 0;
    unsigned int n2 = 0;

    printf(" Number: ");
    n = get_unum();
    printf(" Index: ");
    n2 = get_unum();

    if (n2 % 3 == 0 || (n >> 24) == 0xb7)
    {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    buff[n2 * 4] = n;
    return 0;
}

int read_number(char *buff)
{
    unsigned int index = 0;

    printf(" Index: ");
    index = get_unum();
    printf(" Number at data[%u] is %u\n", index, buff[index * 4]);
    return 0;
}

int main(int argc, char **argv)
{
    // Initialize variables
    char **av = argv;
    char **av_4 = argv + 4;
    unsigned int n = 20;
    unsigned int v1 = 0;
    char cmd[20];
    char buffer[100];

    memset(buffer, 0, sizeof(buffer));
    memset(cmd, 0, sizeof(cmd));

    while (*av != NULL)
    {
        int len = 0;
        while (*av[len] != 0)
            len++;
        memset(*av, 0, len);
        av++;
    }

    while (*av_4 != NULL)
    {
        int len = 0;
        while (av_4[0][len] != 0)
            len++;
        memset(av_4[0], 0, len);
        av_4++;
    }

    puts("----------------------------------------------------");
    puts(" Welcome to wil's crappy number storage service!");
    puts("----------------------------------------------------");
    puts(" Commands:");
    puts(" store - store a number into the data storage");
    puts(" read  - read a number from the data storage");
    puts(" quit  - exit the program");
    puts("----------------------------------------------------");
    puts(" wil has reserved some storage :>");
    puts("----------------------------------------------------");

    while (1)
    {
        printf("Input command: ");
        v1 = 1;
        fgets(cmd, 20, stdin);

        int size = 0;
        while (cmd[size + 1])
            size++;
        cmd[size] = '\0';

        // Check for command and execute
        if (strcmp(cmd, "store") == 0)
            v1 = store_number(buffer);
        else if (strcmp(cmd, "read") == 0)
            v1 = read_number(buffer);
        else if (strcmp(cmd, "quit") == 0)
            return 0;

        if (v1 != 0)
            printf(" Failed to do %s command\n", cmd);
        else
            printf(" Completed %s command successfully\n", cmd);

        memset(cmd, 0, sizeof(cmd));
    }

    return 0;
}