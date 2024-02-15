// main server header file
#include "networking.h"
#include "http.h"
#include "include.h"

// read message from a client and write it to a buffer pointed by *buff
void read_from_client(int *sock_connect, uint8_t *buff);

void write_response(int *sock_connect);

// in a new thread read, parse and interpret a request from a client,
// prepare response and send it, close connection
void *handle_connection(void *sock_connect); 

// main server loop
void main_loop(int *sock_listen);
