#include <stdio.h>

#include "../inc/game_pieces.h"
#include "../inc/netcomm.h"
#include "../inc/packet.h"
#include "../inc/server.h"

char *getPacketType(PacketType packet)
{
    switch (packet)
    {
    case P_CONNECT:
        return "Connect";
    case P_MOVE:
        return "Move";
    case P_DISPLAY_BOARD:
        return "Display Board";
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
        perror("Receive Failed");
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