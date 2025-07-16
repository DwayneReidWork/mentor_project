#pragma once
#include <stdbool.h>
#include <stdint.h>

#include "../inc/packet.h"

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

typedef struct
{
    Pieces piece;
    char *unicode;
    char *name;
} p_unicode_t;

extern game_t *game;
char *piece_name_lookup(Pieces piece);
char *piece_unicode_lookup(Pieces piece);
int display_board();
int new_game_board();