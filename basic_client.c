#include "pipe_networking.h"

int main() {
    int to_server;
    int from_server;

    from_server = client_handshake(&to_server);

    int rand = 0;
    while (1) {
        while (read(from_server, &rand, sizeof(int)) <= 0)
            ;
        printf("Random number: %d\n", rand);
    }
}
