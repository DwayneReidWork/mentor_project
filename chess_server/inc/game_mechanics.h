#pragma once

#include "../inc/game_pieces.h"

char *piece_unicode_lookup(Pieces piece);

int check_valid_move(Pieces piece, int start_row, int start_col, int end_row, int end_col);
int move_piece(Pieces piece, int start_row, int start_col, int end_row, int end_col);
int print_piece_bits(Pieces piece);
int run_game();
int uinput_to_row_col(char *square, int *row, int *col);