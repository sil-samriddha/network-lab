 ### The client will send a set of numbers till `“0”` is entered.After receiving `“0”`, the server will send `SUM` of those numbers to the client.

#### SERVER
```bash
$ gcc server.c -o server
$ ./server
```
```console
Server listening on port 5741
Client connected 127.0.0.1 port : 52794
123456 388999 1073741824 21121223 98367 
Sum : 1095473869
Sent
```

#### CLIENT
```bash
$ gcc client.c -o client
$ ./client
```
```console
Connected to server

Enter numbers :
123456
388999
1073741824
21121223
98367
0
Sum : 1095473869
```

