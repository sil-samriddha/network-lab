# PROBLEM 1.5
### Write a C program to check whether the Host machine is in Little Endian or Big Endian. Enter a number, print the content of each byte location and Convert the Endianness of the same i.e. Little to Big Endian and vice-versa.

## INPUT
```
$ gcc solution.c
$ ./a.out 258
```
## OUTPUT
```
LSB of 258 is : 2
-----------------------
Memory Address  Value
-----------------------
0x7fff44f3c800  2
0x7fff44f3c801  1
0x7fff44f3c802  0
0x7fff44f3c803  0
-----------------------
The LSB of the number is stored at the lowest memory address
Hence the host machine is LITTLE ENDIAN.
Big endian format of the number : 33619968
```