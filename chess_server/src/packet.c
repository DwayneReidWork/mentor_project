#include <stdio.h>
#include <wchar.h>

#include "../inc/game_pieces.h"
#include "../inc/netcomm.h"
#include "../inc/packet.h"
#include "../inc/server.h"

typedef struct
{
    Pieces piece;
    char *unicode;
} p_unicode_t;

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

char *getPacketType(PacketType packet)
{
    switch (packet)
    {
    case P_CONNECT:
        return "Connect";
    case P_MOVE:
        return "Move";
    default:
        // Handle cases where the number doesn't match an enum value
        return "Invalid Packet Type";
    }
}

int receive_packet(int client_sock, p_header_t *header, uint8_t **dest)
{
    printf("Waiting for Packet.\n");

    if (NULL == header)
    {
        perror("Header Invalid");
        return -1;
    }

    if (NULL == dest)
    {
        perror("Dest Invalid");
        return -1;
    }

    ssize_t bytes = recv_expected(client_sock, sizeof(p_header_t), (uint8_t *)header, sizeof(p_header_t));

    printf("Packet Received.\n");
    if (0 > bytes)
    {
        perror("Receive Failed\n");
        return -1;
    }

    printf("Recvd Packet Type: %d\n", header->msg_type);
    printf("Recvd Packet Len: %d\n", htonl(header->p_len));

    *dest = recv_expected_alloc(client_sock, htonl(header->p_len));

    if (NULL == *dest)
    {
        perror("Malloc Failed");
        return -1;
    }

    return header->msg_type;
}

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
        printf("%s\n", pieceptr->unicode);
        if (pieceptr->piece == piece)
            return pieceptr->unicode;
    }
    return "?";
}