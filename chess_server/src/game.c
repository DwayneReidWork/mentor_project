#include <stdint.h>
#include "../inc/game.h"
// later...

uint8_t piece = BLACK | BISHOP;
// test side

int some_func()
{
    if ((piece & WHITE) == WHITE)
    {
        // is white piece
        return 0;
    }
    else
    {
        // is black piece? technically can't assume the black bit is set
        return 0;
    }
    if ((piece & NOCOLOR) == BISHOP)
    {
        // any bishop
        return 0;
    }
    if ((piece & (WHITE | PAWN)) == (WHITE | PAWN))
    {
        // specifically a white pawn
        return 0;
    }
}