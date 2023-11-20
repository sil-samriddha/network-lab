# SOCKET PROGRAMMING
### Write a sender and receiver program in C by passing the IP address and the port number of each other through the command line arguments using connection less socket. Both of them will exchange messages with each other continuously. If any one of them will receive the `“exit”` message from the other end then both of them will close the connection. (Assume both the client and server are running with in the same host)

## CLIENT
```console
$ gcc client.c -o client -w
$ ./client

Socket created
Enter message to send ['exit' to close] : Hello, This is Samriddha from server
Enter message to send ['exit' to close] : Sending text message A B C D 1 2 3 4
Enter message to send ['exit' to close] : :)      
Enter message to send ['exit' to close] : Okay bye !!   
Enter message to send ['exit' to close] : exit
Socket closed

```

## SERVER
```console
$ gcc server.c -o server -w
$ ./server

Socket created
Listening on port 5741
Received message : Hello, This is Samriddha from server
Received message : Sending text message A B C D 1 2 3 4
Received message : :)
Received message : Okay bye !!
Received message : exit
Socket closed
```