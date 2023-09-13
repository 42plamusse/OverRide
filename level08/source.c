#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define LOG_FILE "./backups/.log"
#define MAX_PATH_LENGTH 100

void log_wrapper(FILE *file, const char *msg, const char *path)
{
    char buff[MAX_PATH_LENGTH + 50]; // Ensure buffer is large enough
    int len = strlen(msg);

    if (len >= sizeof(buff))
    {
        fprintf(stderr, "Error: Message too long for log wrapper\n");
        return;
    }

    strncpy(buff, msg, sizeof(buff));
    strncat(buff, path, sizeof(buff) - len - 1); // Leave space for null terminator
    fprintf(file, "LOG: %s\n", buff);
}

int main(int argc, char **argv)
{
    FILE *file, *log;
    char logPath[MAX_PATH_LENGTH];
    char backupPath[MAX_PATH_LENGTH];
    char c;
    int fd;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    log = fopen(LOG_FILE, "w");
    if (log == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open %s\n", LOG_FILE);
        return 1;
    }

    log_wrapper(log, "Starting backup: ", argv[1]);

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open %s\n", argv[1]);
        fclose(log);
        return 1;
    }

    snprintf(logPath, sizeof(logPath), "./backups/%s", LOG_FILE);

    int len = strlen(argv[1]);
    if (len >= MAX_PATH_LENGTH - 11)
    {
        fprintf(stderr, "ERROR: File path is too long\n");
        fclose(file);
        fclose(log);
        return 1;
    }

    snprintf(backupPath, sizeof(backupPath), "./backups/%s", argv[1]);

    fd = open(backupPath, O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (fd < 0)
    {
        fprintf(stderr, "ERROR: Failed to open %s\n", backupPath);
        fclose(file);
        fclose(log);
        return 1;
    }

    while ((c = fgetc(file)) != EOF)
    {
        if (c != 0xff)
        {
            write(fd, &c, 1);
        }
    }

    log_wrapper(log, "Finished backup: ", argv[1]);
    fclose(file);
    close(fd);
    fclose(log);
    return 0;
}
