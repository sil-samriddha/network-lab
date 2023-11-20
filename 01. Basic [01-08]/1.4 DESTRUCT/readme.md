# PROBLEM 1.4
### Write a C Program to enter an integer number of four bytes and store the number across the following structure and print the content of each member of the structure. Then aggregate each member of the structure to form the original number and print the same.
```C
struct pkt{
	char ch1;
	char ch2[2];
	char ch3;
};
```
## INPUT
```
$ gcc solution.c
$ ./a.out 258
```
## OUTPUT
```
1st Member of the structure : 2
2nd Member of the structure : 1, 0
3rd Member of the structure : 0
The regenerated number : 258
```