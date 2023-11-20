### The client will send the message to server and server will return the number of charters in the message to client.

#### SERVER
```bash
$ gcc server.c -o server
$ ./server
```

```console
Server listening on port 5741

Client connected : 127.0.0.1 port: 54692
Received string : Hello world!
Char count : 12
Sent
```

#### CLIENT
```bash
$ gcc client.c -o client
$ ./client
```

```console
Connected to server

Enter string : Hello world!
Total no of chars : 12
```