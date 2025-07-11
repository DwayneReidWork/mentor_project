CC = gcc --std gnu99 -D_GNU_SOURCE

CFLAGS = -Wall -g -I ./inc

# Source and header files
SRCS = chess_server/src/main.c chess_server/src/server.c chess_server/src/packet.c chess_server/src/netcomm.c chess_server/src/game_pieces.c chess_server/src/game_mechanics.c

HDRS = chess_server/inc/server.h chess_server/inc/packet.h chess_server/inc/netcomm.h chess_server/inc/game_pieces.h chess_server/inc/game_mechanics.h

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = chess

# Default rule
all: clean $(EXEC)

# Link object files to create executable
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean rule
clean:
	rm -f $(EXEC) $(OBJS)

# Clean build + valgrind with -v (verbose)
v: clean $(EXEC)
	valgrind -v ./$(EXEC)

# Clean build + valgrind with leak check
vv: clean $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

# Clean build + valgrind with leak check + summary
vvv: clean $(EXEC)
	valgrind --leak-check=full -s ./$(EXEC)

.PHONY: all clean