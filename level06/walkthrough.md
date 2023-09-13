## Vulnerability Type:

Bypassing Debugger Detection

## Walkthrough:

1. The program requests a username and serial number as input.
2. It calculates a key based on the username using a complex algorithm.
   - It XORs the third character of the username with `0x1337`.
   - For each character in the username, it applies multiple operations and updates the key.
3. The generated key is compared to the provided serial number.
4. If the key matches the serial number, the program executes `/bin/sh`.
5. To prevent debugging, the program checks for debugging using `ptrace`. If detected, it terminates.

## Exploitation:

There are two solutions:

- Bypassing the debugging prevention by modifying the `eax` register after the `ptrace` check.
- Write the source code of the program, and print the `keygen` write before the comparison with the `serial`.
