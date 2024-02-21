// HTTP parsing/interpreting header file
#include "include.h"

enum METHOD {
	UNKNOWN,
	GET
};

struct http_request {
	uint8_t method;
	char path[MAXLINE];
};

// parse first line of the request, request line, and fill req struct
void parse_request_line(uint8_t *raw_message, struct http_request *req);

// parse request from a raw string, then fill and return request struct
struct http_request parse_request(uint8_t *raw_message); 

// interpret request struct and prepare response for the client
void prepare_response(struct http_request *req, uint8_t *response);
