// main header file
#include "networking.h"
#include "comm.h"
#include <pthread.h>

void* handle_connection(void *sock_connect) 
{
	// arguments to thread function have to be void pointers
	// translate them to int here
	int *s_conn = (int *)sock_connect;

	read_client_msg(s_conn);
	write_to_client(s_conn);
}

void main_loop(int *sock_listen)
{
	// client address stuff
	SA_IN client_data;
	socklen_t addr_len;
	char client_address[MAXLINE+1];
	
	while(1) {
		int sock_connect; // connection socket
	
		printf("waiting for a connection\n");	
		fflush(stdout);

		// accept connection and don't save client address
		sock_connect = accept(*sock_listen, (SA *)&client_data, 
				&addr_len);

		inet_ntop(AF_INET, &client_data, client_address, MAXLINE);
		printf("Connecting to: %s\n", client_address);

		pthread_t new_thread;
		pthread_create(&new_thread, NULL, handle_connection, 
			&sock_connect);
	}
}
