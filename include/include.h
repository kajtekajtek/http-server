/* Libraries and macros */
#include <stdio.h> // i/o
#include <stdlib.h> //exit()
#include <arpa/inet.h> // sockets
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <netdb.h>
#include <string.h> // memset(),strlen()
#include <stdint.h> // uint8_t
#include <pthread.h> // threads
#include <unistd.h> // read(),write(),close()

// the port clients are connecting to
#define PORT 8000 

// how many pending connections queue will hold
#define BACKLOG 10

// max line length
#define MAXLINE 1024

// max message length
#define MAXMSG 1024

// max http request parameter length
#define MAXREQ 20
