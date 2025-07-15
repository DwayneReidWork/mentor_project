#pragma once

#include "../inc/game_pieces.h"

int run_game();
int print_piece_bits(uint8_t piece);
char *piece_unicode_lookup(Pieces piece);
int check_valid_move(Pieces piece, int start_row, int start_col, int end_row, int end_col);