// client-server communication header file
#include <stdio.h> // i/o
#include <unistd.h> // read(),write(),close()
#include <string.h> // memset(),strlen()
#include <stdint.h> // uint8_t

// max line length
#define MAXLINE 4096

void handle_request(int *sock_connect);

void write_response(int *sock_connect);
