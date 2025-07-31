#pragma once

#include <netinet/in.h>
#include <signal.h>
#include <sys/types.h>

#define DEFAULT_PORT 1234
#define MAX_CONNECTIONS 3
#define SQUARE_SIZE 2

extern volatile sig_atomic_t keep_running;

int handle_client(int client_sock);
int p_connect_method(uint8_t *data);
int p_move_method(uint8_t *data);
int send_board(int socket);
int server_setup(int port);