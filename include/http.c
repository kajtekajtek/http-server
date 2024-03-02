#include "http.h"

// --- Parsing requests
// parse request from a raw string, then fill and return request struct
struct http_request parse_request(uint8_t *raw_message)
{
	struct http_request req;

	parse_request_line(raw_message, &req);

	return req;
}

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

	// check the request method
	if (strcmp(method, "GET") == 0) {
		req_ptr->method = GET;
	} else {
		req_ptr->method = UNKNOWN;
	}
}

// --- Responses
// interpret request struct and prepare response string for the client
void prepare_response(struct http_request *req_ptr, char *response)
{
	switch (req_ptr->method)
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

int read_from_file(char *path, char *buff, size_t *buff_size);

// prepare response to the GET method
void GET_response(struct http_request *req_ptr, char *response)
{
	char *path = req_ptr->path;

	// remove leading slash
	if (path[0] == '/') {
		path += 1;
	}

	// set the path to DEFAULT_FILE if '/' path was requested
	if (!strlen(path)) {
		path = DEFAULT_FILE;
	}

	// first line of the response
	snprintf(response, MAXMSG, 
		"HTTP/1.1 200 OK\r\n\r\n");

	// current response size + terminating zero
	size_t response_size = strlen(response) + 1;

	// read from file and return 404 on error
	if (read_from_file(path, response, &response_size) > 0) {
		memset(response, 0, sizeof(response));
		snprintf(response, MAXMSG, 
			"HTTP/1.1 404 Not Found\r\n\r\n");

		path = NULL;
		return;
	}

	path = NULL;
}
