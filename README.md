# TCP client and server

Server - prints received bytes to the console. Runs continuously until killed

Client - sends static message to address passed

## Requirements
- gcc

## How to use
```gcc tcp_server.c -o server```

```gcc tcp_client.c -o client```

```./server 127.0.0.1 8000``` 

```./client 127.0.0.1 8000```
