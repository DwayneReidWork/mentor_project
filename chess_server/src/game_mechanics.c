#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/game_mechanics.h"
#include "../inc/game_pieces.h"

int run_game()
{
    // game stuff
    game = malloc(sizeof(game_t));
    if (NULL == game)
    {
        perror("malloc");
        return 1;
    }

    memset(game, 0, sizeof(game_t));

    new_game_board();
    display_board();

    // free(game);
    return 0;
}

int print_piece_bits(Pieces piece)
{
    // Determine the number of bits in the unsigned int type
    int num_bits = sizeof(uint8_t) * 8;

    for (int i = num_bits - 1; i >= 0; i--)
    {
        // Create a mask with a '1' at the current bit position
        // and '0's elsewhere.
        // Use bitwise AND to check if the bit at the current position is set.
        // If (num & mask) is non-zero, the bit is 1; otherwise, it's 0.

        printf("%d", (piece & (1 << i)) != 0);
    }
    printf("\n");
    return 0;
}

int uinput_to_row_col(char *square, int *row, int *col)
{
    if (strlen(square) != 2)
    {
        printf("Invalid square format: %s\n", square);
        return -1;
    }

    char file = tolower(square[0]);
    char rank = square[1];

    if (file < 'a' || file > 'h')
    {
        printf("Invalid file (col): %c\n", file);
        return -1;
    }
    *col = file - 'a';

    if (rank < '1' || rank > '8')
    {
        printf("Invalid rank (row): %c\n", rank);
        return -1;
    }
    *row = 8 - (rank - '0');
    return 0;
}

int check_valid_move(Pieces piece, int start_row, int start_col, int end_row, int end_col)
{
    int direction, home_row, intermediate_row, row_diff, col_diff, dir_x, dir_y, step_x, step_y, x, y;

    bool valid_move = false;

    Pieces target, intermediate_target;

    if ((piece & COLOR_MASK) == EMPTY)
    {
        printf("You selected an Empty start square.\n");
        valid_move = false;
        return valid_move;
    }

    switch (piece & NOCOLOR)
    {
    case PAWN:
        if (piece & WHITE)
        {
            printf("White Pawn\n");
            direction = -1;
            home_row = 6;
        }
        else
        {
            printf("Black Pawn\n");
            direction = 1;
            home_row = 1;
        }
        row_diff = end_row - start_row;
        col_diff = end_col - start_col;

        target = game->board[end_row][end_col];

        if (row_diff == direction && col_diff == 0)
        {
            if ((target & NOCOLOR) == EMPTY)
            {
                valid_move = true;
                break;
            }
            else
            {
                printf("Blocked! Can't move forward to occupied square.\n");
                valid_move = false;
            }
        }
        else if (row_diff == 2 * direction && col_diff == 0 && start_row == home_row)
        {
            intermediate_row = start_row + direction;
            intermediate_target = game->board[intermediate_row][start_col];

            if ((intermediate_target & NOCOLOR) == EMPTY && (target & NOCOLOR) == EMPTY)
            {
                valid_move = true;
            }
            else
            {
                printf("2 Step move blocked.\n");
                valid_move = false;
            }
        }
        else if (row_diff == direction && abs(col_diff) == 1)
        {
            if ((PieceType)target != EMPTY && ((target & COLOR_MASK) != (piece & COLOR_MASK)))
            {
                valid_move = true;
                break;
            }
            else
            {
                printf("No enemy piece to capture diagonally.\n");
                valid_move = false;
            }
        }
        else
        {
            printf("Invalid Pawn Move.\n");
            valid_move = false;
        }
        break;
    case KNIGHT:
        printf("Knight\n");
        break;
    case BISHOP:
        printf("Bishop\n");
        dir_x = end_row - start_row;
        dir_y = end_col - start_col;

        if (abs(dir_x) == abs(dir_y))
        {
            // Ternary conditional check (same from python)
            // variable = condition ? value_if_true : value_if_false;

            step_x = (dir_x > 0) ? 1 : -1;
            step_y = (dir_y > 0) ? 1 : -1;

            x = start_col + step_y;
            y = start_row + step_x;

            while ((x != end_col) && (y != end_row))
            {
                printf("Checking square [%d][%d]...\n", y, x);
                if (game->board[y][x] != EMPTY)
                {
                    printf("Path is blocked!\n");
                    valid_move = false;
                    break;
                }
                else
                {
                    x += step_y;
                    y += step_x;
                }
                valid_move = true;
            }
        }
        else
        {
            printf("Invalid Bishop Move");
            valid_move = false;
        }
        break;
    case ROOK:
        printf("Rook\n");
        break;
    case QUEEN:
        printf("Queen\n");
        break;
    case KING:
        printf("King\n");
        // Currently only has logic for moving not castling
        dir_x = end_row - start_row;
        dir_y = end_col - start_col;
        if (abs(dir_x) <= 1 && abs(dir_y) <= 1)
        {
            valid_move = true;
        }
        else
        {
            printf("Invalid King Move");
            valid_move = false;
        }
        break;
    default:
        printf("Unknown piece\n");
        break;
    }
    return valid_move;
}

int move_piece(Pieces piece, int start_row, int start_col, int end_row, int end_col)
{
    if (start_row < 0 || start_row > 7 || start_col < 0 || start_col > 7 ||
        end_row < 0 || end_row > 7 || end_col < 0 || end_col > 7)
    {
        printf("Attempting to move to invalid board position.\n");
        return -1;
    }
    game->board[start_row][start_col] = EMPTY;
    game->board[end_row][end_col] = piece;
    return 0;
}