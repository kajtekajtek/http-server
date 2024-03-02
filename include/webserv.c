#include "webserv.h"

// open and read requested file, then save it contents to a buffer
int read_from_file(char *path, char *buff, size_t *buff_size)
{
	FILE *file_ptr;
	char chunk[MAXLINE + 1];
	int bytes_read;

	// open the file
	if ((file_ptr = fopen(path, "r")) == NULL) {
		// error
		return 1;
	}

	printf("%s", buff);
	
	// read from the file iteratively in chunks
	while((bytes_read = fread(chunk, 1, MAXLINE, file_ptr)) > 0) {
		// check if there's enough space in the buffer
		if (*buff_size + bytes_read >= MAXMSG) {
			perror("reading file error; buffer overflow");
			fclose(file_ptr);
			return 1;
		}

		// concatenate the chunk to the buffer
		strcat(buff, chunk);

		// update the buffer size
		*buff_size += bytes_read;
	}

	// check for the read error
	if (ferror(file_ptr)) {
		perror("reading file error");
		fclose(file_ptr);
		return 1;
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
	uint8_t raw_message[MAXMSG + 1]; 
	// response
	char response[MAXMSG + 1];

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
