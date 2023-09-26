## TCP CONNECTION
```bash
$ gcc server.c -o server -w
$ gcc client.c -o client -w
```
## SERVER
```bash
$ ./server
```
```console
Socket Created
Done with binding
Listening on 127.0.0.1:5741
Accepted new client : 127.0.0.1 | 42656
Received message : Hello, From client

Enter for sending message : Hello, From server
[Message sent]
Received message : Finish

Enter for sending message : Exit
[Message sent]
Socket closed
```

## CLIENT
```bash
$ ./client
```
```console
Socket created
Connected to server
Enter message for sending ['Exit' to close] : Hello, From client
[Message Sent]
Received from server : Hello, From server

Enter message for sending ['Exit' to close] : Finish                           
[Message Sent]
Received from server : Exit

Socket closed
```
