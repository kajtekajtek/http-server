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

// attach requested body to the response
void get_requested_body(const struct http_request *req, char *response);

// prepare response to the GET method
void GET_response(const struct http_request *req, char *response);

// interpret request struct and prepare response for the client
void prepare_response(const struct http_request *req, char *response);
