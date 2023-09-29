## TCP DATA QUERY & FETCH
```bash
$ gcc server.c -o server -w
$ ./server
```
```bash
$ gcc client.c -o client -w
$ ./client
```
## SERVER
```console
Socket created
Memory Allocated : 480 bytes
Data fetched     : 7 items 
Listening on : 127.0.0.1 | Port : 5741
New Client : 127.0.0.1 | Port : 54880
Socket closed
```

## CLIENT
```console
Connected to server
Enter user id : 2107
Displaying information
Name    : Norma Webster
Age     : 23
Height  : 75
Weight  : 145
Socket closed
```