#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{

    char username_buffer[0x64];
    char stored_password[0x2a];
    char password_buffer[0x64];

    size_t pwd_len = 0;
    FILE *file = 0;

    memset(username_buffer, 0, 12);
    memset(stored_password, 0, 5);
    memset(password_buffer, 0, 12);

    file = fopen("/home/users/level03/.pass", "r");
    if (!file)
    {
        fwrite("ERROR: failed to open password file\n", 1, 0x24, stderr);
        exit(1);
    }

    pwd_len = fread(stored_password, 1, sizeof(stored_password) - 1, file);
    stored_password[strcspn(stored_password, "\n")] = 0;
    if (pwd_len != sizeof(stored_password) - 1)
    {
        fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
        exit(1);
    }

    fclose(file);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(username_buffer, 0x64, stdin);
    username_buffer[strcspn(username_buffer, "\n")] = 0;

    printf("--[ Password: ");
    fgets(password_buffer, 0x64, stdin);
    password_buffer[strcspn(password_buffer, "\n")] = 0;
    puts("*****************************************");

    if (strncmp(stored_password, password_buffer, sizeof(stored_password)))
    {
        printf(username_buffer);
        puts(" does not have access!");
        exit(1);
    }

    printf("Greetings, %s!\n", username_buffer);
    system("/bin/sh");

    return 0;
}