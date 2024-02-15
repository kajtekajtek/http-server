#include "webserv.h"

// return and argument have to be void pointers since this is a new thread
// function
void *handle_connection(void *sock_connect) 
{
	// client message buffer
	uint8_t raw_message[MAXLINE]; 
	// request information struct to fill up
	struct http_request req;

	read_from_client(sock_connect, raw_message);
	
	req = parse_request(raw_message);

	printf("%s\n", raw_message);

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
