#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../inc/game.h"

uint8_t board[8][8];

void print_piece_bits(uint8_t piece)
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
}

int uinput_to_row_col(char *square, int *row, int *col)
{
    int _row, _col;
    printf("Square: %s\n", square);

    if (strlen(square) != 2)
    {
        perror("Invalid square.\n");
        return -1;
    }

    _row = square[1] - '0';
    printf("_row: %d\n", _row);
    if (_row < 0 || _row > 8)
    {
        printf("Invalid Row.");
        return -1;
    }
    *row = _row;

    _col = square[0] - '`';
    printf("_col: %d\n", _col);
    if (_col < 0 || _col > 8)
    {
        printf("Invalid Col.");
        return -1;
    }
    *col = _col;

    return 0;
}
// // later...

// uint8_t piece = BLACK | BISHOP;
// // test side

// int some_func()
// {
//     if ((piece & WHITE) == WHITE)
//     {
//         // is white piece
//         return 0;
//     }
//     else
//     {
//         // is black piece? technically can't assume the black bit is set
//         return 0;
//     }
//     if ((piece & NOCOLOR) == BISHOP)
//     {
//         // any bishop
//         return 0;
//     }
//     if ((piece & (WHITE | PAWN)) == (WHITE | PAWN))
//     {
//         // specifically a white pawn
//         return 0;
//     }
// }