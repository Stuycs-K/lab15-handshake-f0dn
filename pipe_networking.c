#include "pipe_networking.h"
#include <stdio.h>

// UPSTREAM = to the server / from the client
// DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
    mkfifo(WKP, 0644);

    int from_client = open(WKP, O_RDONLY);

    remove(WKP);

    return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's
  private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
    int from_client = server_setup();

    int pid = 0;
    while (read(from_client, &pid, sizeof(int)) <= 0)
        ;

    printf("Received syn: %d\n", pid);

    char buffer[HANDSHAKE_BUFFER_SIZE];
    sprintf(buffer, "%d", pid);

    *to_client = open(buffer, O_WRONLY);

    srand(pid);
    int random = rand();
    write(*to_client, &random, sizeof(int));

    printf("Sent syn_ack: %d\n", random);

    int ack = 0;
    while (read(from_client, &ack, sizeof(int)) <= 0)
        ;

    printf("Received ack: %d\n", ack);

    if (ack != random + 1) {
        printf("Handshake failed\n");
        exit(1);
    }

    return from_client;
}

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
    char buffer[HANDSHAKE_BUFFER_SIZE];
    sprintf(buffer, "%d", getpid());
    mkfifo(buffer, 0644);

    *to_server = open(WKP, O_WRONLY);
    int pid = getpid();
    write(*to_server, &pid, sizeof(int));

    printf("Sent syn: %d\n", pid);

    int from_server = open(buffer, O_RDONLY);
    remove(buffer);

    int syn_ack = 0;
    while (read(from_server, &syn_ack, sizeof(int)) <= 0)
        ;

    printf("Received syn_ack: %d\n", syn_ack);

    syn_ack++;
    write(*to_server, &syn_ack, sizeof(int));

    printf("Sent ack: %d\n", syn_ack);

    return from_server;
}

/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
    int to_client = 0;
    return to_client;
}
