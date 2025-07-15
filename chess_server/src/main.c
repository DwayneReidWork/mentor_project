#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../inc/game_mechanics.h"
#include "../inc/server.h"

int main(int argc, char *argv[])
{
    int port = DEFAULT_PORT;
    if (1 < argc)
    {
        // atoi converts string to int
        port = atoi(argv[1]);
    }
    server_setup(port);

    run_game();
    return 0;
}