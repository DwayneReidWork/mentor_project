#pragma once

#include <netinet/in.h>
#include <sys/types.h>

#define MAX_USERNAME_LEN 128
typedef uint8_t chess_piece;

typedef enum __attribute__((__packed__))
{
    P_CONNECT = 1, // Eventually Login/Register
    P_MOVE,
} PacketType;

char *getPacketType(PacketType packet);

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

char *piece_unicode_lookup(Pieces piece);

// Packet Type (Header for All)
typedef struct __attribute__((__packed__))
{
    // msg_tpe is specific type of PacketType
    PacketType msg_type;
    uint32_t p_len;
} p_header_t;

typedef struct __attribute__((__packed__))
{
    p_header_t header;
    // uint32_t port;
    uint32_t username_len;
    char user_name[MAX_USERNAME_LEN];
} p_connection_t;

typedef struct __attribute__((__packed__))
{
    p_header_t header;
    char from_square[2];
    char to_square[2];
    chess_piece promotee;
} p_move_t;

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