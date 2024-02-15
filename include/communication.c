#include "communication.h"

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

struct http_request parse_request(uint8_t *raw_message)
{
	// parse request and fill request struct
}

void write_response(int *sock_connect)
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
