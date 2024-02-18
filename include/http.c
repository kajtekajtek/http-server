#include "http.h"

void parse_request_line(uint8_t *raw_message, struct http_request *req)
{
	char method[MAXREQ] = { 0 };

	// separate substrings of the first line of the message
	// first substring is a method, second is a path
	// ignore third (protocol version)
	if (sscanf(raw_message, "%s %s %s", method, &req->path, 
		NULL) == EOF) {
		perror("request line parsing error");
	}

	if (strcmp(method, "GET ") != 0) {
		req->method = GET;
	} else {
		req->method = UNKNOWN;
	}
}

struct http_request parse_request(uint8_t *raw_message)
{
	struct http_request req;

	parse_request_line(raw_message, &req);

	return req;
}
