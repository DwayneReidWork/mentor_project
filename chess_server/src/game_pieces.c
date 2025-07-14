#include <stdio.h>

#include "../inc/game_pieces.h"
#include "../inc/packet.h"

game_t *game = NULL;

p_unicode_t piece_lookup[] = {
    {.piece = EMPTY, .unicode = "."},
    {.piece = BLACK_PAWN, .unicode = "\xe2\x99\x9f"},
    {.piece = BLACK_KNIGHT, .unicode = "\xe2\x99\x9e"},
    {.piece = BLACK_BISHOP, .unicode = "\xe2\x99\x9d"},
    {.piece = BLACK_ROOK, .unicode = "\xe2\x99\x9c"},
    {.piece = BLACK_QUEEN, .unicode = "\xe2\x99\x9b"},
    {.piece = BLACK_KING, .unicode = "\xe2\x99\x9a"},
    {.piece = WHITE_PAWN, .unicode = "\xe2\x99\x99"},
    {.piece = WHITE_KNIGHT, .unicode = "\xe2\x99\x98"},
    {.piece = WHITE_BISHOP, .unicode = "\xe2\x99\x97"},
    {.piece = WHITE_ROOK, .unicode = "\xe2\x99\x96"},
    {.piece = WHITE_QUEEN, .unicode = "\xe2\x99\x95"},
    {.piece = WHITE_KING, .unicode = "\xe2\x99\x94"},
};

int new_game_board()
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            game->board[r][c] = EMPTY;

    // Black Pieces
    for (int i = 0; i < 8; i++)
    {
        game->board[1][i] = BLACK_PAWN;
    }

    game->board[0][0] = BLACK_ROOK;
    game->board[0][7] = BLACK_ROOK;
    game->board[0][1] = BLACK_KNIGHT;
    game->board[0][6] = BLACK_KNIGHT;
    game->board[0][2] = BLACK_BISHOP;
    game->board[0][5] = BLACK_BISHOP;
    game->board[0][3] = BLACK_KING;
    game->board[0][4] = BLACK_QUEEN;

    // White
    for (int j = 0; j < 8; j++)
    {
        game->board[6][j] = WHITE_PAWN;
    }
    game->board[7][0] = WHITE_ROOK;
    game->board[7][7] = WHITE_ROOK;
    game->board[7][1] = WHITE_KNIGHT;
    game->board[7][6] = WHITE_KNIGHT;
    game->board[7][2] = WHITE_BISHOP;
    game->board[7][5] = WHITE_BISHOP;
    game->board[7][3] = WHITE_KING;
    game->board[7][4] = WHITE_QUEEN;

    return 0;
};

/// @brief Lookup function for unicode of given chess piece
/// @param piece
/// @return unicode of chess piece or ? on err
char *piece_unicode_lookup(Pieces piece)
{
    size_t list_size = sizeof(piece_lookup) / sizeof(piece_lookup[0]);
    p_unicode_t *pieceptr;

    for (int x = 0; x < list_size; x++)
    {
        pieceptr = piece_lookup + x;
        if (pieceptr->piece == piece)
            return pieceptr->unicode;
    }
    return "?";
}

int display_board()
{
    printf("    A   B   C   D   E   F   G   H\n");
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (int row = 0; row < 8; row++)
    {
        int display_row = 8 - row;
        printf("%d |", display_row);

        for (int col = 0; col < 8; col++)
        {
            Pieces piece = game->board[row][col];
            printf(" %s |", piece_unicode_lookup(piece));
        }

        printf(" %d\n", display_row);
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    printf("    A   B   C   D   E   F   G   H\n");

    return 0;
}