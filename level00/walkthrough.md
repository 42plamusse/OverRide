# Level0

## Vulnerability type:

Input Validation

## Walkthrough:

The simple C program compares an input integer to 0x149c (5276 in decimal).
To exploit, provide the integer 5276 as input to trigger the system call and execute /bin/sh.

## Payload:

Manually exploit by echoing '5276' and redirecting it to the program.
Automate the exploit using Python and the pwn library.

```
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```
