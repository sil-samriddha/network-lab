## TCP DATA QUERY & FETCH
```bash
$ gcc server.c -o server -w
$ ./server
```
```bash
$ gcc client.c -o client -w
$ ./client
```
### DATA
| UserID |       Name       | Age | Height | Weight (pound) |
|--------|------------------|-----|--------|-----------------|
|  2101  |   Adarsh Hota   |  39 |   77   |      231       |
|  2102  |    Levi Maier   |  56 |   77   |      129       |
|  2103  |  Priya Kumari   |  63 |   78   |      240       |
|  2104  | Dorothy Helton  |  47 |   72   |      229       |
|  2105  | Florence Smith  |  24 |   75   |      171       |
|  2106  |   Erica Anyan   |  38 |   73   |      102       |
|  2107  |  Norma Webster  |  23 |   75   |      145       |

## TEST CASE 1
### SERVER
```console
Socket created
Memory Allocated : 480 bytes
Data fetched     : 7 items 
Listening on : 127.0.0.1 | Port : 5741
New Client : 127.0.0.1 | Port : 54880
Socket closed
```

### CLIENT
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

## TEST CASE 2
### SERVER
```console
Socket created
Memory Allocated : 480 bytes 
Data fetched     : 7 items
Listening on : 127.0.0.1 | Port : 5741
New Client : 127.0.0.1 | Port : 55804
Socket closed
```
### CLIENT
```console
Connected to server
Enter user id : 1234
User not found
Socket closed
```