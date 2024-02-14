// networking header file
#include <stdio.h> // i/o
#include <stdlib.h> //exit()
#include <string.h> // memset()
#include <arpa/inet.h> // sockets
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <netdb.h>

// the port clients are connecting to
#define PORT 8000 

// how many pending connections queue will hold
#define BACKLOG 10

#define SA struct sockaddr 
#define SA_IN struct sockaddr_in 

void bind_listener(int *sock_listen);

void listen_on(int *sock_listen);
