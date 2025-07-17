#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <wchar.h>

#include "../inc/game_mechanics.h"
#include "../inc/game_pieces.h"
#include "../inc/netcomm.h"
#include "../inc/packet.h"
#include "../inc/server.h"

volatile sig_atomic_t keep_running = 1;

void ctrlc_handler(int dummy)
{
    const char *error_message = "\nCTRL+C signal received.\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
    keep_running = 0;
}

int signal_handler_setup()
{
    struct sigaction sa;
    sa.sa_handler = ctrlc_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction SIGINT");
        return -1;
    }
    return 0;
}

int handle_client(int client_sock)
{
    p_header_t header;
    ssize_t bytes = recv_expected(client_sock, sizeof(p_header_t), (uint8_t *)&header, sizeof(p_header_t));

    printf("Packet Received.\n");
    if (0 > bytes)
    {
        perror("Receive Failed\n");
        return -1;
    }

    printf("Received header: %s\n", getPacketType(header.msg_type));
    printf("Recvd Packet Type: %d\n", header.msg_type);
    printf("Recvd Packet Len: %d\n", htonl(header.p_len));

    uint8_t *data = recv_expected_alloc(client_sock, htonl(header.p_len));

    if (NULL == data)
    {
        perror("Malloc Failed");
        return -1;
    }

    // meat of the game
    int packet_type = header.msg_type;

    switch (packet_type)
    {
    case P_CONNECT:
        p_connect_method(data);
        break;
    case P_MOVE:
        p_move_method(data);
        break;
    case P_DISPLAY_BOARD:
        printf("Display board packet recieved\n");
        display_board();
        break;
    default:
        printf("Invalid Packet Type Received\n");
        break;
    }
    return 0;
}

int server_setup(int port)
{
    if (0 != signal_handler_setup())
    {
        perror("Signal Handler Error");
        return -1;
    }
    // Server Setup Stuff
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int status = 0;
    int addrlen = sizeof(address);

    if (-1 == (server_fd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("Socket Failure");
        return -1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        close(server_fd);
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (0 > bind(server_fd, (struct sockaddr *)&address, sizeof(address)))
    {
        perror("bind failed");
        close(server_fd);
        return -1;
    }

    if (0 > listen(server_fd, 3))
    {
        perror("listen failed");
        close(server_fd);
        return -1;
    }

    printf("Listening on port %d.\n", port);

    if (0 > (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)))
    {
        perror("accept failed");
        close(server_fd);
        return -1;
    }
    char host_buff[NI_MAXHOST];
    char port_buff[NI_MAXSERV];

    if (0 != (status = getnameinfo((struct sockaddr *)&(address), addrlen, host_buff, NI_MAXHOST, port_buff, NI_MAXSERV, NI_NUMERICSERV)))
    {
        fprintf(stderr, "Failed to get name information for client (%d: %s)", status, gai_strerror(status));
        return -1;
    }

    printf("Connection Recieved from %s:%s\n", host_buff, port_buff);

    while (0 != keep_running)
    {
        if (0 > handle_client(new_socket))
        {
            perror("Error Handling Client");
            break;
        }
    }

    printf("\nShutting down server...\n");
    close(new_socket);
    close(server_fd);
    return 0;
}

int p_connect_method(uint8_t *data)
{
    printf("Connection Request Received!\n");
    p_connection_t c_pack;
    // copy from data stream into struct
    memcpy(&c_pack.username_len, data, sizeof(c_pack.username_len));
    c_pack.username_len = htonl(c_pack.username_len);
    // copy to length -1 for null term
    if (c_pack.username_len > MAX_USERNAME_LEN - 1)
    {
        c_pack.username_len = MAX_USERNAME_LEN - 1;
    }
    memcpy(&c_pack.user_name, data + sizeof(c_pack.username_len), c_pack.username_len);
    // null term username
    c_pack.user_name[c_pack.username_len] = '\0';
    printf("Username Received: %s\n", c_pack.user_name);
    run_game();

    return 0;
}

int p_move_method(uint8_t *data)
{
    printf("Move Request Received!\n");
    // copy recieved data into move pack struct
    p_move_t mv_pak;
    memcpy(&mv_pak.from_square, data, 2);
    memcpy(&mv_pak.to_square, data + 3, 2);
    // null term moves
    mv_pak.from_square[2] = '\0';
    mv_pak.to_square[2] = '\0';

    printf("Received move from %.2s to %.2s.\n", mv_pak.from_square, mv_pak.to_square);

    // convert start and end squares to row/col
    int start_row, start_col, end_row, end_col;
    uinput_to_row_col(mv_pak.from_square, &start_row, &start_col);
    Pieces piece = game->board[start_row][start_col];
    printf("From Square\nRow: %d, Column: %d\n", start_row, start_col);
    uinput_to_row_col(mv_pak.to_square, &end_row, &end_col);
    printf("To square\nRow: %d, Column: %d\n", end_row, end_col);

    if (check_valid_move(piece, start_row, start_col, end_row, end_col))
    {
        Pieces end_piece = game->board[end_row][end_col];
        // if space is empty or occupied by opposite color piece
        if ((end_piece == (Pieces)EMPTY) ||
            ((piece & WHITE) && (end_piece & BLACK)) ||
            ((piece & BLACK) && (end_piece & WHITE)))
        {
            // move
            move_piece(piece, start_row, start_col, end_row, end_col);
        }
        else if ((end_piece == (Pieces)EMPTY) ||
                 ((piece & WHITE) && (end_piece & WHITE)) ||
                 ((piece & BLACK) && (end_piece & BLACK)))
        {
            printf("Space Occupied by same color piece. Invalid Move.\n");
        }
    }
    display_board();
    return 0;
}