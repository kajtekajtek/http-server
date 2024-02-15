// HTTP parsing/interpreting header file
#include "include.h"

struct http_request {
	uint8_t method;
	uint8_t path[MAXLINE];
};

// parse request from a raw string, then fill and return request struct
struct http_request parse_request(uint8_t *raw_message); 

