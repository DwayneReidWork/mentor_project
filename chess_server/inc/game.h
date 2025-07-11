#pragma once

#include <stdint.h>
#include <stdbool.h>

void print_piece_bits(uint8_t piece);

typedef struct
{
    char player_name[50];
    int turn;
    bool game_over;
    uint8_t board_state[8][8];
} game_state;
