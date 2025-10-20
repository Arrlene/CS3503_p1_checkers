CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -O2

SRC=src/main.c src/bitops.c src/bitboard.c src/game.c
OBJ=$(SRC:.c=.o)
BIN=bitcheckers

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(BIN)