#include "webserv.h"

void read_from_client(int *sock_connect, uint8_t *buff)
{
	int n; // read() result

	memset(buff, 0, MAXLINE);
	while((n = read(*sock_connect, buff, MAXLINE-1)) > 0) {
		// newline terminates
		if (buff[n-1] == '\n') {
			break;
		}
	}

	if (n < 0) {
		perror("read error");
	}
}

void write_response(int *sock_connect)
{
	uint8_t buff[MAXLINE+1];

	// write response to a buffer
	snprintf((char*)buff, sizeof(buff),
			"HTTP/1.1 200 OK\r\n\r\nHello");

	// send response
	if (write(*sock_connect, (char*)buff, strlen((char*)buff)) < 0) {
		perror("write error");
	}

	close(*sock_connect);
}

// return and argument have to be void pointers since this is a new thread
// function
void *handle_connection(void *sock_connect) 
{
	// client message buffer
	uint8_t raw_message[MAXLINE]; 
	// request information struct to fill up
	struct http_request req;
	// response
	uint8_t response[MAXLINE];

	read_from_client(sock_connect, raw_message);
	
	req = parse_request(raw_message);

	// treat sock_connect as an int pointer
	close(*(int*)sock_connect);

	return NULL;
}

void main_loop(int *sock_listen)
{
	int sock_connect; // connection socket
	// client address stuff
	SA_IN client_data;
	socklen_t addr_len;
	char client_address[MAXLINE+1];
	
	while(1) {
		printf("waiting for a connection\n");	
		fflush(stdout);

		// accept connection and don't save client address
		sock_connect = accept(*sock_listen, (SA *)&client_data, 
				&addr_len);

		inet_ntop(AF_INET, &client_data, client_address, MAXLINE);
		printf("Connecting to: %s\n", client_address);

		pthread_t new_thread;
		int conn_to_handle = sock_connect;
		pthread_create(&new_thread, NULL, handle_connection, 
			&conn_to_handle);
	}
}
