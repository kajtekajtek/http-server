#include "http.h"

// parse first line of the request, request line, and fill req struct
void parse_request_line(uint8_t *raw_message, struct http_request *req_ptr)
{
	char method[MAXREQ] = { 0 };

	// separate substrings of the first line of the message
	// first substring is a method, second is a path
	// ignore third (protocol version)
	if (sscanf(raw_message, "%s %s %s", method, &req_ptr->path, 
		NULL) == EOF) {
		perror("request line parsing error");
	}

	if (strcmp(method, "GET") == 0) {
		req_ptr->method = GET;
	} else {
		req_ptr->method = UNKNOWN;
	}
}

// parse request from a raw string, then fill and return request struct
struct http_request parse_request(uint8_t *raw_message)
{
	struct http_request req;

	parse_request_line(raw_message, &req);

	return req;
}

void get_requested_body(const struct http_request *req_ptr, char *response)
{
	// check if requested file exists
	// get requested body if the file is found
	// write body to a buffer or signalize error
	FILE file_ptr;
}

// prepare response to the GET method
void GET_response(const struct http_request *req_ptr, char *response)
{
	snprintf(response, MAXMSG, 
		"HTTP/1.1 200 OK\r\n\r\n");
}

// interpret request struct and prepare response string for the client
void prepare_response(const struct http_request *req_ptr, char *response)
{
	switch (req->method)
	{
		case GET:
			// attach requested body to the response
			GET_response(req_ptr, response);
			break;
		default:
			// error
			snprintf(response, MAXMSG, 
				"HTTP/1.1 400");
			break;
	}	
}
