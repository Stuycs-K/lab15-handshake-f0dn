#include "pipe_networking.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    srand(time(NULL));

    int to_client;
    int from_client;

    from_client = server_handshake(&to_client);

    while (1) {
        int r = rand() % 100;
        write(to_client, &r, sizeof(int));
        sleep(1);
    }
}
