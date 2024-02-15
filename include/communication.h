// client-server communication header file
#include <stdio.h> // i/o
#include <unistd.h> // read(),write(),close()
#include <string.h> // memset(),strlen()
#include <stdint.h> // uint8_t

// max line length
#define MAXLINE 4096

// request methods
//enum method {
//	GET,
//	HEAD,
//	POST,
//	PUT,
//	DELETE,
//	CONNECT,
//	OPTIONS,
//	TRACE
//};

struct http_request {
	uint8_t method;
	uint8_t path[MAXLINE];
};

// read message from a client and write it to a buffer pointed by *buff
void read_from_client(int *sock_connect, uint8_t *buff);

// parse request and fill request struct
struct http_request parse_request(uint8_t *raw_message); 

void write_response(int *sock_connect);
