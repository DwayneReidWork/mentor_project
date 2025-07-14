#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/game_mechanics.h"

int run_game()
{
    // game stuff
    game = malloc(sizeof(game_t));
    if (NULL == game)
    {
        perror("Failed to allocate memory for game\n");
        return 1;
    }

    memset(game, 0, sizeof(game_t));

    new_game_board();
    display_board();

    free(game);
    return 0;
}

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