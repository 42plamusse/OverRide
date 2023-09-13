#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ptrace.h>

int auth(char *login, unsigned int serial)
{
    int len;
    unsigned int keygen;

    login[strcspn(login, "\n")] = 0;

    len = strnlen(login, 0x20);
    if (len <= 5)
        return (1);

    if (ptrace(PT_TRACE_ME, 0, 1, 0) == -1)
    {
        puts("\x1B[32m.---------------------------.");
        puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
        puts("\x1B[32m'---------------------------'");
        return 1;
    }
    else
    {
        keygen = (login[3] ^ 0x1337) + 6221293;
        for (int i = 0; i < len; ++i)
        {
            if (login[i] <= 31)
                return 1;
            keygen += (keygen ^ (unsigned int)login[i]) % 0x539;
        }
        return serial != keygen;
    }
}

int main(void)
{
    char login[0x20];
    unsigned int serial;

    puts("***********************************\n");
    puts("*		level06		  *\n");
    puts("***********************************\n");
    printf("-> Enter Login: ");
    fgets(login, 0x20, stdin);

    puts("***********************************\n");
    puts("***** NEW ACCOUNT DETECTED ********\n");
    puts("***********************************\n");
    printf("-> Enter Serial: ");
    scanf("%u", &serial);

    if (auth(login, serial))
        return (1);

    puts("Authenticated!\n");
    system("/bin/sh");
    return (0);
}