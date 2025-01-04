#include "pipe_networking.h"
#include <ctype.h>

int main() {
    int to_client;
    int from_client;

    from_client = server_handshake(&to_client);

    char buffer[BUFFER_SIZE];
    while (1) {
        while (read(from_client, buffer, sizeof(buffer)) <= 0)
            ;
        printf("Received: %s\n", buffer);

        char *p = buffer;
        while (*p) {
            if (isalpha(*p))
                *p = tolower(*p);
            p++;
        }
        write(to_client, buffer, sizeof(buffer));
    }
}
