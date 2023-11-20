### Client will send a string to the server and server will count how many words, characters, vowels in it, and sent it to client.

#### SERVER
```bash
$ gcc server.c -o server
$ ./server
```
```console
Server listening on port 5741

Client connected : 127.0.0.1 port: 50988
Received string : Hello World
Result Sent
```

#### CLIENT
```bash
$ gcc client.c -o client
$ ./client
```

```console
Connected to server

Enter string : Hello World
Total no of chars : 12
Total no of words : 2
Total no of vowels : 3
```