#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024
#define BACKLOG 5


int main(int argc, char const *argv[])
{
    struct sockaddr_in server;  // server (self) address info
    int sock;                   // server (self) socket
    int inSock;                 // incoming connection's socket
    char buf[BUF_SIZE];         // message buffer
    int chNum;                  // number of characters read

    // parse arguments
    if (argc != 3) {
        printf("wrong number of arguments\n");
        printf("try: ./<f_name> <host_addr_ipv4> <host_port>\n");
        exit(1);
    }
    const char* host = argv[1];
    const int port = atoi(argv[2]);

    // configure server (self) address
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host);
    memset(server.sin_zero, '\0', sizeof server.sin_zero);

    // ----------------------------------------------------

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Error creating socket\n");
        exit(1);
    }

    if (bind(sock, (struct sockaddr *) &server, sizeof server) == -1) {
        printf("Could not bind address %s\n", host);
        exit(1);
    }
    printf("Socket succesfully binded at %s:%d\n",
           inet_ntoa(server.sin_addr),
           ntohs(server.sin_port));

    if (listen(sock, BACKLOG) == -1) {
        perror("Error listening\n");
        exit(1);
    }

    while (1) {
        printf("\nWaiting for incoming connection\n");

        inSock = accept(sock, (struct sockaddr *) 0, (socklen_t *) sizeof server);
        if (inSock == -1) {
            perror("Could not accept\n");
            exit(1);
        }
        printf("Connected\n");

        do { // read data
            memset(buf, 0, sizeof buf);
            if ((chNum = read(inSock, buf, BUF_SIZE)) == -1) {
                perror("Could not read data\n");
                exit(1);
            }
            else if (chNum == 0) {
                printf("All read. Ending connection\n");
            }
            else {
                printf("Data -> %s\n", buf);
            }
        } while (chNum > 0);

        close(inSock);
    }
    return 0;
}
