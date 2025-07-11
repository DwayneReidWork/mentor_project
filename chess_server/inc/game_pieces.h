#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    EMPTY = 0,
    PAWN = 1 << 1,
    KNIGHT = 1 << 2,
    BISHOP = 1 << 3,
    ROOK = 1 << 4,
    QUEEN = 1 << 5,
    KING = 1 << 6,
    WHITE = 1 << 7,
    BLACK = 1 << 8,
    NOCOLOR = 0b00111111,
    // added for attacks
    COLOR_MASK = WHITE | BLACK,
} PieceType;

typedef enum
{
    WHITE_KING = WHITE | KING,
    WHITE_QUEEN = WHITE | QUEEN,
    WHITE_ROOK = WHITE | ROOK,
    WHITE_BISHOP = WHITE | BISHOP,
    WHITE_KNIGHT = WHITE | KNIGHT,
    WHITE_PAWN = WHITE | PAWN,
    BLACK_KING = BLACK | KING,
    BLACK_QUEEN = BLACK | QUEEN,
    BLACK_ROOK = BLACK | ROOK,
    BLACK_BISHOP = BLACK | BISHOP,
    BLACK_KNIGHT = BLACK | KNIGHT,
    BLACK_PAWN = BLACK | PAWN,
} Pieces;

typedef struct
{
    PieceType board[8][8];
    bool win;
    bool left_castle_open;
    bool right_castle_open;
} game_t;

// EMPTY_SQUARE = 0x20,
//     WHITE_KING = 0x2654,
//     WHITE_QUEEN = 0x2655,
//     WHITE_ROOK = 0x2656,
//     WHITE_BISHOP = 0x2657,
//     WHITE_KNIGHT = 0x2658,
//     WHITE_PAWN = 0x2659,
//     BLACK_KING = 0x265A,
//     BLACK_QUEEN = 0x265B,
//     BLACK_ROOK = 0x265C,
//     BLACK_BISHOP = 0x265D,
//     BLACK_KNIGHT = 0x265E,
//     BLACK_PAWN = 0x265F