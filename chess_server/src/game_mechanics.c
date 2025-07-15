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

    free(game);
    return 0;
}

int print_piece_bits(uint8_t piece)
{
    // Determine the number of bits in the unsigned int type
    int num_bits = sizeof(uint8_t) * CHAR_BIT;

    for (int i = num_bits - 1; i >= 0; i--)
    {
        // Create a mask with a '1' at the current bit position
        // and '0's elsewhere.
        unsigned int mask = 1U << i;

        // Use bitwise AND to check if the bit at the current position is set.
        // If (num & mask) is non-zero, the bit is 1; otherwise, it's 0.
        printf("%d", (piece & mask) ? 1 : 0);
    }
    printf("\n");
    return 0;
}

int uinput_to_row_col(char *square, int *row, int *col)
{
    // Takes in a square and splits it into row and column and assignes the values to pointers
    int _row, _col;
    if (strlen(square) != 2)
    {
        perror("Invalid square.\n");
        return -1;
    }

    _row = square[1] - '1';
    if (_row < 0 || _row > 8)
    {
        printf("Invalid Row.");
        return -1;
    }
    *row = _row;

    _col = square[0] - 'a';
    if (_col < 0 || _col > 8)
    {
        printf("Invalid Col.");
        return -1;
    }
    *col = _col;

    return 0;
}

int check_valid_move(Pieces piece, int start_row, int start_col, int end_row, int end_col)
{
    bool valid_move = false;
    switch (piece & NOCOLOR)
    {
    case PAWN:
        printf("Pawn\n");
        int direction, home_row, intermediate_row, row_diff, col_diff;
        Pieces target;

        if (piece & WHITE)
        {
            direction = -1;
            home_row = 6;
        }
        else
        {
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
            printf("Intermediate row: %d", intermediate_row);
        }
        return valid_move;

        break;
    case KNIGHT:
        printf("Knight\n");
        break;
    case BISHOP:
        printf("Bishop\n");
        break;
    case ROOK:
        printf("Rook\n");
        break;
    case QUEEN:
        printf("Queen\n");
        break;
    case KING:
        printf("King\n");
        break;
    case EMPTY:
        printf("Empty\n");
        break;
    default:
        printf("Unknown piece\n");
        break;
    }
    return 0;
}