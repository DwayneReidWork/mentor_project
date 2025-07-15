#pragma once

#include <netinet/in.h>
#include <stdbool.h>
#include <sys/types.h>

#include "../inc/game_pieces.h"

#define MAX_USERNAME_LEN 128

typedef enum __attribute__((__packed__))
{
    P_CONNECT = 1, // Eventually Login/Register
    P_MOVE,
} PacketType;

char *getPacketType(PacketType packet);

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
    char from_square[3];
    char to_square[3];
    uint8_t promotee;
} p_move_t;

typedef struct
{
    char player_name[50];
    int turn;
    bool game_over;
    uint8_t board_state[8][8];
} game_state;