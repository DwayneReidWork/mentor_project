#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

#include "../inc/game.h"
#include "../inc/server.h"
#include "../inc/packet.h"

int main(int argc, char *argv[])
{
    int port = DEFAULT_PORT;
    if (1 < argc)
    {
        // atoi converts string to int
        port = atoi(argv[1]);
    }

    server_setup(port);
    return 0;
}