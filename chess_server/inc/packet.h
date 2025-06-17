#pragma once

#include <netinet/in.h>
#include <sys/types.h>

/*
 board = [
        ['r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'],
        ['p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'],
        ['.', '.', '.', '.', '.', '.', '.', '.'],
        ['.', '.', '.', '.', '.', '.', '.', '.'],
        ['.', '.', '.', '.', '.', '.', '.', '.'],
        ['.', '.', '.', '.', '.', '.', '.', '.'],
        ['P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'],
        ['R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R']
    ]
 */

typedef enum __attribute__((__packed__))
{
    CONNECT = 1, // Eventually Login/Register
    MOVE,
    BOARD_STATE,
} PacketType;

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
    uint8_t board_state[8][8];
} p_board_state_t;

typedef struct __attribute__((__packed__))
{
    // msg_tpe is specific type of PacketType
    p_header_t header;
    uint8_t board_state[8][8];
    uint8_t move;
} p_move_t;