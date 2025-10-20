#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>

typedef struct {
    uint64_t p1; 
    uint64_t p1k;
    uint64_t p2;  
    uint64_t p2k; 
    int turn;    
} GameState;

void game_init(GameState* g);
void print_board(const GameState* g);
int try_move(GameState* g, int from, int to);
int has_winner(const GameState* g);
int square_occupied(const GameState* g, int pos);
int current_player_can_move_simple(const GameState* g);
int is_dark_square(int pos);

#endif