#pragma once

#include <stdint.h>

// Make the highest bits represent black or white
#define WHITE 0b10000000
#define BLACK 0b01000000
#define NOCOLOR 0b00111111

// each bit represents a piece
#define PAWN 1 << 0   // 0b00000001
#define KNIGHT 1 << 1 // 0b00000010
#define BISHOP 1 << 2 // 0b00000100
#define ROOK 1 << 3   // 0b00001000
#define QUEEN 1 << 4  // 0b00010000
#define KING 1 << 5   // 0b00100000

// later...

uint8_t piece = BLACK | BISHOP;
// test side

if ((piece & WHITE) == WHITE)
{
    // is white piece
}
else
{
    // is black piece? technically can't assume the black bit is set
}
if ((piece & NOCOLOR) == BISHOP)
{
    // any bishop
}
if ((piece & (WHITE | PAWN)) == (WHITE | PAWN))
{
    // specifically a white pawn
}