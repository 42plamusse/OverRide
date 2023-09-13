#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
// #include <sys/prctl.h>

int main(void)
{
    int p_id;
    char buffer[0x20];
    int status;

    p_id = fork();
    memset(buffer, 0, 0x20);

    if (p_id == 0) // child
    {
        prctl(1, 1);
        ptrace(PT_TRACE_ME, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(buffer);
    }
    else
    {
        while (42)
        {
            wait(&status);
            if (WIFEXITED(status) || WIFSIGNALED(status))
            {
                puts("child is exiting...");
                break;
            }
            else
            {
                if (ptrace(3, p_id, 0x2c, 0) == 0xb)
                {
                    puts("no exec() for you");
                    kill(p_id, SIGKILL);
                    break;
                }
            }
        }
    }
}