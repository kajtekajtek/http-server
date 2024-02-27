#include "webserv.h"

// open and read requested file, then save it contents to a buffer
int read_from_file(char *path, char *buff)
{
	FILE *file_ptr;

	// open the file
	if ((file_ptr = fopen(path, "r")) == NULL) {
		// error
		return 1;
	}

	
	// read from the file
	while(fgets(buff, MAXLINE, file_ptr) != NULL) {
		// reads only last line; in progress
	}


	// close the file
	fclose(file_ptr);

	return 0;
}

// read message from a client and write it to a buffer pointed by *buff
void read_from_client(int *sock_connect, uint8_t *buff)
{
	int n; // read() result

	memset(buff, 0, MAXMSG);
	while((n = read(*sock_connect, buff, MAXMSG - 1)) > 0) {
		// newline terminates
		if (buff[n-1] == '\n') {
			break;
		}
	}

	if (n < 0) {
		perror("read error");
	}
}

void write_response(int *sock_connect, char *res)
{
	// write response to a buffer
//	snprintf((char*)buff, sizeof(buff), res);

	// send response
	if (write(*sock_connect, res, strlen(res)) < 0) {
		perror("write error");
	}

	close(*sock_connect);
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

// return and argument have to be void pointers since this is a new thread
// function
void *handle_connection(void *sock_connect) 
{
	// request information struct to fill up
	struct http_request req;
	// client message buffer
	uint8_t raw_message[MAXMSG]; 
	// response
	char response[MAXMSG];
	//printf("%d", sizeof(response));

	memset(raw_message, 0, MAXMSG);
	memset(response, 0, MAXMSG);

	read_from_client(sock_connect, raw_message);
	
	req = parse_request(raw_message);

	prepare_response(&req, response);

	write_response(sock_connect, response);

	// treat sock_connect as an int pointer
	close(*(int*)sock_connect);

	return NULL;
}
