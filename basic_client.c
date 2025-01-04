#include "pipe_networking.h"

int main() {
    int to_server;
    int from_server;

    from_server = client_handshake(&to_server);

    char buffer[BUFFER_SIZE];
    while (1) {
        printf("Enter a message: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strlen(buffer) - 1] = 0;

        write(to_server, buffer, sizeof(buffer));

        while (read(from_server, buffer, sizeof(buffer)) <= 0)
            ;
        printf("Received: %s\n", buffer);
    }
}
