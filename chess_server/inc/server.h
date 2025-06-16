#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/types.h>

#define DEFAULT_PORT 1234
#define DEFAULT_PORT_STR "1234"
#define BUFFER_SIZE 1024
#define MAX_CONNECTIONS 5

int server_setup(int port);
int handle_client(int client_sock);

#endif