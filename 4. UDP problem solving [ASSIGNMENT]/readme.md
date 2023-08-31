## UDP SOCKET PROBLEM
### CLient will send two integer numbers to the server and the task of the server is to add two numbets and send to the client as response.

## SERVER
```console
$ gcc server.c -o server -w
$ ./server

Socket created
Server running on 127.0.0.1
Port : 5741
Waiting for client ...
Request from client port : 36429
Two integers : 70 84
70 + 84 = 154
Socket closed
```

## CLIENT
```console
$ gcc client.c -o client -w
$ ./client

Socket created
Connecting to server : 127.0.0.1 : 5741

Enter two integer numbers :
70 84

Request send to the server
Waiting for response from server...

Addition of two numbers : 154
Socket closed
```