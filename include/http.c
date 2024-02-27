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

int read_from_file(char *path, char *buff);

// prepare response to the GET method
void GET_response(struct http_request *req_ptr, char *response)
{
	char *path = req_ptr->path;
	char response_body[MAXLINE];
	
	memset(response_body, 0, MAXLINE);

	strcpy(path, req_ptr->path);

	// remove leading slash
	if (path[0] == '/') {
		path += 1;
	}

	// set the path to DEFAULT_FILE if '/' path was requested
	if (!strlen(path)) {
		path = DEFAULT_FILE;
	}

	// read from file and return 404 on error
	if (read_from_file(path, response_body) > 0) {
		snprintf(response, MAXMSG, 
			"HTTP/1.1 404 Not Found\r\n\r\n");
		return;
	}

	// everything's fine
	snprintf(response, MAXMSG, 
		"HTTP/1.1 200 OK\r\n\r\n");

	// concatenate response with body
	strcat(response, response_body);
}


