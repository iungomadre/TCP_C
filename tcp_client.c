#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATA "abcdefghijklmnoprstuwxyz"

int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in server;

    if (argc != 3) {
        perror("wrong number of arguments\n");
        perror("try: ./<f_name> <host> <port>\n");
        exit(1);
    }
    const char* host = argv[1];
    const int port = atoi(argv[2]);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Could not initiate socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &server.sin_addr) == -1) {
        perror("Invalid address");
        exit(1);
    }

    if (connect(sock, (struct sockaddr *) &server, sizeof server) == -1) {
        perror("Could not connect to server");
        exit(1);
    }

    if (write(sock, DATA, sizeof DATA) == -1) {
        perror("Could not send data");
        exit(1);
    }

    close(sock);
    return 0;
}
