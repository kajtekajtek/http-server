// networking header file
#include "include.h"

#define SA struct sockaddr 
#define SA_IN struct sockaddr_in 

void bind_listener(int *sock_listen);

void listen_on(int *sock_listen);
