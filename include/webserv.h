// main header file
#include "networking.h"
#include "comm.h"
#include <pthread.h>

void * handle_connection(void *sock_connect); 

void main_loop(int *sock_listen);
