## SERVER
```console
$ gcc server.c -o server -w
$ ./server

Socket created
IPv4 address :  127.0.0.1
Port no :       5741

Waiting for client...

Received message : Hello, I'm client requesting from server
[ Client Address : 127.0.0.1 ] [ Port : 38392 ]
Sending message : Hello, I'm server sending data to client

Waiting for client...

Received message : what is the sum of 3 and 4
[ Client Address : 127.0.0.1 ] [ Port : 38392 ]
Sending message : sum of 3 and 4 is 7

Waiting for client...

Received message : Send my IP and Port
[ Client Address : 127.0.0.1 ] [ Port : 38392 ]
Sending message : IPv4 127.0.0.1 Port 38392

Waiting for client...

Received message : exit
[ Client Address : 127.0.0.1 ] [ Port : 38392 ]
Sending message : exit
Socket closed
```

## CLIENT
```console
$ gcc client.c -o client -w
$ ./client 127.0.0.1 5741

Socket created
[Connected to server 127.0.0.1 : 5741]

Enter message to send : Hello, I'm client requesting from server
[Message sent]

Received message : Hello, I'm server sending data to client


Enter message to send : what is the sum of 3 and 4
[Message sent]

Received message : sum of 3 and 4 is 7


Enter message to send : Send my IP and Port
[Message sent]

Received message : IPv4 127.0.0.1 Port 38392


Enter message to send : exit
[Message sent]
Socket closed

```