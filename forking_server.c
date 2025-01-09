#include "pipe_networking.h"
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void sig_handler(int signo) {
    if (signo == SIGINT) {
        remove(WKP);
        exit(1);
    }
}

int main() {
    srand(time(NULL));
    signal(SIGINT, sig_handler);
    signal(SIGPIPE, SIG_IGN);

    while (1) {
        int to_client;
        int from_client;

        from_client = server_handshake(&to_client);

        remove(WKP);
        int pid = fork();

        if (pid == 0) {
            while (1) {
                int r = rand() % 100;
                int res = write(to_client, &r, sizeof(int));
                sleep(1);
                if (res == -1) {
                    printf("client disconnected\n");
                    break;
                }
            }
            exit(1);
        }
    }

    remove(WKP);
}
