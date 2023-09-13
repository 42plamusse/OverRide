#include <stdio.h>
#include <string.h>

char username[0x64];

int verify_user_name(char *username)
{
    puts("verifying username....\n");

    return memcmp(username, "dat_wil", 7);
}

int verify_user_pass(char *password)
{
    return memcmp(username, "admin", 5);
}

int main()
{
    char password[0x40];
    int isValid;

    memset(password, 0, sizeof(password));
    isValid = 0;

    puts("********* ADMIN LOGIN PROMPT *********\n");

    printf("Enter Username: ");
    fgets(username, 0x100, stdin);

    isValid = verify_user_name(username);
    if (isValid != 0)
    {
        puts("nope, incorrect username...\n");

        return (1);
    }

    printf("Enter Password: ");
    fgets(password, 0x64, stdin);

    isValid = verify_user_pass(password);

    puts("nope, incorrect password...\n");

    if (isValid == 0)
        return (1);
    else
        return (0);
}