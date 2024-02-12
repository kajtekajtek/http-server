#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SA struct sockaddr 
#define SA_IN struct sockaddr_in 

// the port clients are connecting to
#define PORT 8000

// how many pending connections queue will hold
#define BACKLOG 10

// max line length
#define MAXLINE 10

void bind_listener(int *sock_listen) 
{
	// prepare server information
	SA_IN servinfo;

	memset(&servinfo, 0, sizeof servinfo);
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

void read_client_msg(int *sock_connect)
{
	uint8_t recvline[MAXLINE+1];
	int n; // read() result

	memset(recvline, 0, MAXLINE);
	while((n = read(*sock_connect, recvline, MAXLINE-1)) > 0) {
		printf("\n%s\n", recvline);

		// newline terminates
		if (recvline[n-1] == '\n') {
			break;
		}
		memset(recvline, 0, MAXLINE);
	}

	if (n < 0) {
		perror("read error");
	}
}

void write_to_client(int *sock_connect)
{
	uint8_t buff[MAXLINE+1];

	// write response to a buffer
	snprintf((char*)buff, sizeof(buff),
			"HTTP/1.0 200 OK\r\n\r\nHello");

	// send response
	if (write(*sock_connect, (char*)buff, strlen((char*)buff)) < 0) {
		perror("write error");
	}

	close(*sock_connect);
}

void main_loop(int *sock_listen)
{
	int sock_connect; // connection socket
	
	while(1) {
		printf("waiting for a connection\n");	
		fflush(stdout);

		// listening socket, don't save connecting socket's address
		sock_connect = accept(*sock_listen, (SA *) NULL, NULL);

		read_client_msg(&sock_connect);

		write_to_client(&sock_connect);
	}
}
