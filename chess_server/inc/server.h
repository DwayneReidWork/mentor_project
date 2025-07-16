#pragma once

#include <netinet/in.h>
#include <signal.h>
#include <sys/types.h>

#define DEFAULT_PORT 1234
#define DEFAULT_PORT_STR "1234"
#define BUFFER_SIZE 1024

extern volatile sig_atomic_t keep_running;

int handle_client(int client_sock);
int server_setup(int port);