#include "../include/webserv.h"

int main(int argc, char* argv[])
{
	int sock_listen; // socket to listen on

	bind_listener(&sock_listen);

	listen_on(&sock_listen);

	main_loop(&sock_listen);

	close(sock_listen);

	return 0;
}
