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

    // parse arguments
    if (argc != 3) {
        perror("wrong number of arguments\n");
        perror("try: ./<f_name> <host> <port>\n");
        exit(1);
    }
    const char* host = argv[1];
    const int port = atoi(argv[2]);

    // configure server (self) address
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host);
    memset(server.sin_zero, '\0', sizeof server.sin_zero);

    // ------------------------------------

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Could not initiate socket");
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
