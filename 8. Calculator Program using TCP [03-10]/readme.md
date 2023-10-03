## SIMPLE BASIC CALCULATOR - TCP
```bash
$ gcc server.c -o server -w
$ gcc client.c -o client -w
```

## TEST CASE 1
### SERVER
```bash
$ ./server
```
```console
Socket Created
Done with binding
Listening on 127.0.0.1 port 5741

CLient conected : 127.0.0.1 Port : 56642
Request processing for
 100 * 20
Result = 2000

Socket closed
```

### CLIENT
```bash
$ ./client
```
```console
Socket created
Connected to server

Choose any operator :
+  Addition
-  Substitution
*  Multiplication
/  Division

Operator : %
Number 1 : 26
Number 2 : 33
Operation not supported
Socket closed
```

## TEST CASE 2
### SERVER
```bash
$ ./server
```
```console
Socket Created
Done with binding
Listening on 127.0.0.1 port 5741

CLient conected : 127.0.0.1 Port : 56646
Request processing for
 26 % 33
Operation not supported

Socket closed
```

### CLIENT
```bash
$ ./client
```
```console
Socket created
Connected to server

Choose any operator :
+  Addition
-  Substitution
*  Multiplication
/  Division

Operator : %
Number 1 : 26
Number 2 : 33
Operation not supported
Socket closed
```