// socket_server.c
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SOCKET_PATH "/tmp/mysocket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buffer[256];
    
    /*
    AF_UNIX mean that we are comminicating in the unix machine via file 
path, and not over the network 

    SOCK_STREAM means that we are using TCP-like connection.
    we can have UDP-like connection by the flag SOCK_DGRAM
    */
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(1);
    }

    // Clean up previous socket file if it exists
    unlink(SOCKET_PATH);

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    /*
	We bind the socket to address, which in our case is a file path.
	In case of TCP socket, it will be IP/port binding.
    */
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("bind");
        exit(1);
    }

    /*
	We allow this socket to accept messages.
	Up to 5 messages allowed in the queue in this case. 
    */
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        exit(1);
    }

    printf("Server listening at %s\n", SOCKET_PATH);

    /*
	Server calls accept(), which:

	Checks if there is a client connection waiting in the queue (created by listen()).

	If none, blocks (waits) until a client connects (unless the socket is non-blocking).

	When a client connects, accept():

		- Removes that connection from the queue.

		- Creates a new socket descriptor (file descriptor) dedicated to the client.

		- Returns this new descriptor to the server.

		- Server uses the new descriptor to communicate with the client (via read(), write(), send(), recv()).
    */
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) {
        perror("accept");
        exit(1);
    }

    int bytes = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("Received message: %s\n", buffer);
    }

    // Send reply to client
    const char *reply = "Hello from server!";
    write(client_fd, reply, strlen(reply));

    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);

    return 0;
}

