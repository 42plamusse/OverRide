# Level08

## Vulnerability type:

Path traversal vulnerability

## Walkthrough:

The provided binary is designed to create a backup copy of a file specified as a command-line argument. It does this by opening two files using `fopen()` and one file using `open()`. If any of these operations fail, the program exits.

Here's a breakdown of how the program works:

- The first `fopen()` call attempts to open the file `/backups/.log`. If successful, it logs backup-related messages to this log file.

- The second `fopen()` call attempts to open the file specified in the `av[1]` argument path. This file is the one the program aims to back up.

- The `open()` call creates a file at the path `./backups/` concatenated with the `av[1]` argument path. It then copies the contents from the second `fopen()` file into this newly created file.

The vulnerability lies in the fact that the program does not properly sanitize or verify the paths it constructs for the backup files. It directly concatenates the provided file path with `./backups/`, which makes it susceptible to path traversal attacks.

## Exploitation and payload:

To exploit this path traversal vulnerability, we can create a fake directory structure in the `/tmp/` directory that matches the path to the `/home/users/level09/.pass` file. By doing this, we can trick the program into opening and backing up the contents of the `/home/users/level09/.pass` file to a location of your choice.

Here are the steps to exploit the vulnerability:

1. Create the necessary directory structure in `/tmp/`:

   ```bash
   mkdir -p /tmp/backups/home/users/level09/
   ```

2. Run the vulnerable binary with the manipulated path to trigger the backup:

   ```bash
   cd /tmp
   ~/level08 /home/users/level09/.pass
   ```

3. Check the content of the newly created backup file to verify the success of the exploit:
   ```bash
   cat /tmp/backups/home/users/level09/.pass
   ```
