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

// - Socket operations ----------------------------------------------------

void bind_listener(int *sock_listen) 
{
	// prepare server information
	SA_IN servinfo;

	memset(&servinfo, 0, sizeof(servinfo));
	// internet address
	servinfo.sin_family = AF_INET;
	// responding to any
	servinfo.sin_addr.s_addr = htonl(INADDR_ANY);
	// port to listen on
	servinfo.sin_port = htons(PORT);

	// Create socket
	// internet address, TCP, unspecified default protocol
	if ((*sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		exit(1);
	}	

	// Set options
	// set the REUSEADDR option to 1
	int yes = 1;
	if (setsockopt(*sock_listen, SOL_SOCKET, SO_REUSEADDR, &yes, 
		sizeof(int)) < 0) {
		perror("setsockopt error");
		exit(1);
	}

	// Bind socket
	// socket to be bound, pointer to an address in SA structure,
	// length of a SA structure
	if ((bind(*sock_listen, (SA *)&servinfo, sizeof(servinfo))) < 0) {
		perror("bind error");
		exit(1);
	}
}

// Listen on socket
void listen_on(int *sock_listen) 
{
	if (listen(*sock_listen, BACKLOG) < 0) {
		perror("listen");
		exit(1);
	}
}
