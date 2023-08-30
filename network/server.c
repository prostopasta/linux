#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024
#define PORT_NUMBER 8080

int main () {
    // server socket file descriptor
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Populate server structure
    struct sockaddr_in server = {
            .sin_family      = AF_INET,
            .sin_port        = htons(PORT_NUMBER),
            .sin_addr.s_addr = htonl(INADDR_LOOPBACK),
    };

    // bind to address and start listener
    bind(server_fd, (struct sockaddr *) &server, sizeof(server));

    listen(server_fd, 128);

    printf("Server is listening on %d\n", PORT_NUMBER);

    struct sockaddr_in client;
    char buf[BUFFER_SIZE]; // buffer for echo data
    socklen_t client_len = sizeof(client);

    // accept will block until client connection
    int client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);

    // receive data from client
    ssize_t read_size = recv(client_fd, buf, BUFFER_SIZE, 0);
    printf("read %zd bytes from client\n", read_size);

    // send data back
    send(client_fd, buf, read_size, 0);

    close(client_fd);
    close(server_fd);
}