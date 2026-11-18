#include <stdlib.h>

#include "../inc/game_mechanics.h"
#include "../inc/server.h"

int main(int argc, char *argv[])
{
    int port = DEFAULT_PORT;
    if (1 < argc)
    {
        // // atoi converts string to int
        // atoi is BAD!
        // port = atoi(argv[1]);
        port = (int)strtol(argv[1], NULL, 10);
    }

    server_setup(port);
    return 0;
}