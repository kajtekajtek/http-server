// main header file
#include "networking.h"
#include "communication.h"
#include <pthread.h>

// in a new thread read, parse and interpret a request from a client,
// prepare response and send it, close connection
void *handle_connection(void *sock_connect); 

// main server loop
void main_loop(int *sock_listen);
