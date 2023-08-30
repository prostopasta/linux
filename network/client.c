#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024
#define PORT_NUMBER 8080

int main () {
    // client socket file descriptor
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Populate server structure
    struct hostent *he = gethostbyname("localhost");
    struct sockaddr_in server = {
            .sin_family = AF_INET,
            .sin_port   = htons(PORT_NUMBER),
            .sin_addr   = *((struct in_addr *)he->h_addr),
    };

    // connect to server
    connect(client_fd, (struct sockaddr*)&server, sizeof(server));

    send(client_fd, "Hello, world!\n", 14, 0);

    char buf[BUFFER_SIZE]; // buffer for echo data
    int len = read(client_fd, buf, BUFFER_SIZE);
    printf("read %d bytes from server back\n", len);

    close(client_fd);
}