# SOCKET PROGRAMMING
### Write a sender and receiver program in C by passing the IP address and the port number of each other through the command line arguments using connection less socket. Both of them will exchange messages with each other continuously. If any one of them will receive the `“exit”` message from the other end then both of them will close the connection. (Assume both the client and server are running with in the same host)

## SERVER
```console
$ gcc serverprog.c -o server -w
$ ./server

Socket created
Server running : 127.0.0.1 (port : 5741)
Enter message to send ['exit' to close] : Hello, This is Samriddha from server
Enter message to send ['exit' to close] : Sending text message A B C D 1 2 3 4
Enter message to send ['exit' to close] : :)      
Enter message to send ['exit' to close] : Okay bye !!   
Enter message to send ['exit' to close] : exit
Socket closed

```

## CLIENT
```console
$ gcc clientprog.c -o client -w
$ ./client

Socket created
Listing on port 5741
Received message : Hello, This is Samriddha from server
Received message : Sending text message A B C D 1 2 3 4
Received message : :)
Received message : Okay bye !!
Received message : exit
Socket closed
```