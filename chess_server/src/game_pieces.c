#include <stdio.h>
#include <string.h>

#include "../inc/game_pieces.h"
#include "../inc/packet.h"

game_t *game = NULL;

p_unicode_t piece_lookup[] = {
    {.piece = EMPTY, .unicode = "."},
    {.piece = BLACK_PAWN, .unicode = "\xe2\x99\x9f", .name = "BLACK PAWN"},
    {.piece = BLACK_KNIGHT, .unicode = "\xe2\x99\x9e", .name = "BLACK KNIGHT"},
    {.piece = BLACK_BISHOP, .unicode = "\xe2\x99\x9d", .name = "BLACK BISHOP"},
    {.piece = BLACK_ROOK, .unicode = "\xe2\x99\x9c", .name = "BLACK ROOK"},
    {.piece = BLACK_QUEEN, .unicode = "\xe2\x99\x9b", .name = "BLACK QUEEN"},
    {.piece = BLACK_KING, .unicode = "\xe2\x99\x9a", .name = "BLACK KING"},
    {.piece = WHITE_PAWN, .unicode = "\xe2\x99\x99", .name = "WHITE PAWN"},
    {.piece = WHITE_KNIGHT, .unicode = "\xe2\x99\x98", .name = "WHITE KNIGHT"},
    {.piece = WHITE_BISHOP, .unicode = "\xe2\x99\x97", .name = "WHITE BISHOP"},
    {.piece = WHITE_ROOK, .unicode = "\xe2\x99\x96", .name = "WHITE ROOK"},
    {.piece = WHITE_QUEEN, .unicode = "\xe2\x99\x95", .name = "WHITE QUEEN"},
    {.piece = WHITE_KING, .unicode = "\xe2\x99\x94", .name = "WHITE KING"},
};

int new_game_board()
{
    // Empty Board
    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
            game->board[r][c] = EMPTY;

    // Set Black Pieces
    for (int i = 0; i < BOARD_SIZE; i++)
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

    // Set White Pieces
    for (int j = 0; j < BOARD_SIZE; j++)
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

/// @brief
/// @param piece
/// @return
char *piece_name_lookup(Pieces piece)
{
    size_t list_size = sizeof(piece_lookup) / sizeof(piece_lookup[0]);
    p_unicode_t *pieceptr;

    for (int x = 0; x < list_size; x++)
    {
        pieceptr = piece_lookup + x;
        if (pieceptr->piece == piece)
            return pieceptr->name;
    }
    return "?";
}

int display_board()
{
    printf("    A   B   C   D   E   F   G   H\n");
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        int display_row = BOARD_SIZE - row;
        printf("%d |", display_row);

        for (int col = 0; col < BOARD_SIZE; col++)
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