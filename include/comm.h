// client-server communication header file
#include <stdio.h> // i/o
#include <unistd.h> // read(),write(),close()
#include <string.h> // memset(),strlen()
#include <stdint.h> // uint8_t

// max line length
#define MAXLINE 4096

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