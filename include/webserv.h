// main header file
#include "networking.h"
#include "comm.h"
#include <pthread.h>

// return and argument have to be void pointers since this is a new thread
// function
void * handle_connection(void *sock_connect) 
{
	handle_request(sock_connect);
	write_response(sock_connect);

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
