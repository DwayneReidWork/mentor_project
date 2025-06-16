CC = gcc --std gnu99

CFLAGS = -Wall -g

# Source and header files
SRCS = chess_server/src/main.c chess_server/src/game.c chess_server/src/server.c
HDRS = chess_server/inc/game.h chess_server/inc/server.h

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = chess
# Default rule
all: clean $(EXEC)

# Link object files to create executable
$(EXEC): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean rule
clean:
	rm -f $(EXEC) $(OBJS)

#Valgrind
v:
	valgrind -v ./$(EXEC)

#valgrind with leakcheck
vv:
	valgrind --leak-check=full ./$(EXEC)


.PHONY: all clean