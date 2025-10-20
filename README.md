Author: Arlene Huerta
Course: CS 3503
Project: P1: BitBoard Checkers
Date: 10/20/2025

Commands:
p            print board
m FROM TO    move (indices 0..63)
s FILE       save game to FILE
l FILE       load game from FILE
q            quit

Test log: run ./bitcheckers < tests/session1.txt > tests/session1.out

# BitBoard Checkers (P1)
## Build
```
make
```
## Run
```
./bitcheckers
```


The board prints with rows 0..7 and columns 0..7. Use indices 0..63 (row*8+col).
- `m FROM TO` makes a move (diagonal step or capture).

- Regular pieces move forward; kings moves both ways.
- Promotion happens when a regular piece reaches the far row.
- Captures removes the jumped piece.
- Game ends when a player has no pieces.

## Files
- `src/bitops.*` basic bit ops for Phase 1.
- `src/bitboard.*` bitboard state and helpers.
- `src/game.c` CLI loop.
- `src/main.c` included inside `game.c` (single `main`).

This meets the rubric items: bit ops implemented and 64-bit board; moves/captures/kings; clear display and input; win detection!

