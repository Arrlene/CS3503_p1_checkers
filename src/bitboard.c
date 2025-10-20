// Arlene Huerta
// CS 3503 Project 1: BitBoard Checkers

#include "bitboard.h"
#include <stdio.h>

static int row_of(int pos){ return pos/8; }
static int col_of(int pos){ return pos%8; }

int is_dark_square(int pos){
    if(pos < 0 || pos >= 64) return 0;
    int r=row_of(pos), c=col_of(pos);
    return ((r + c) % 2)==1;
}

static uint64_t mask(int pos){
    if(pos < 0 || pos >= 64) return 0ull;
    return 1ull << pos;
}

int square_occupied(const GameState* g, int pos){
    uint64_t m = mask(pos);
    return (g->p1|g->p1k|g->p2|g->p2k) & m ? 1:0;
}

static int is_p1_piece(const GameState* g, int pos){
    uint64_t m = mask(pos);
    return (g->p1 & m) || (g->p1k & m);
}
static int is_p2_piece(const GameState* g, int pos){
    uint64_t m = mask(pos);
    return (g->p2 & m) || (g->p2k & m);
}
static int is_king(const GameState* g, int pos){
    uint64_t m = mask(pos);
    return (g->p1k & m) || (g->p2k & m);
}

void game_init(GameState* g){
    g->p1 = 0ull; g->p1k = 0ull; g->p2 = 0ull; g->p2k = 0ull; g->turn = 1;
    for(int r=0;r<3;r++){
        for(int c=0;c<8;c++){
            int pos=r*8+c;
            if(is_dark_square(pos)) g->p1 |= mask(pos);
        }
    }
    for(int r=5;r<8;r++){
        for(int c=0;c<8;c++){
            int pos=r*8+c;
            if(is_dark_square(pos)) g->p2 |= mask(pos);
        }
    }
}

void print_board(const GameState* g){
    printf("\n   ");
    for(int c=0;c<8;c++) printf(" %d", c);
    printf("\n");
    for(int r=7;r>=0;r--){
        printf("%d |", r);
        for(int c=0;c<8;c++){
            int pos=r*8+c;
            char ch='.';
            uint64_t m = mask(pos);
            if(g->p1 & m) ch='r';
            if(g->p1k & m) ch='R';
            if(g->p2 & m) ch='b';
            if(g->p2k & m) ch='B';
            printf(" %c", ch);
        }
        printf(" | %d\n", r);
    }
    printf("   ");
    for(int c=0;c<8;c++) printf(" %d", c);
    printf("\nTurn: P%d\n", g->turn);
}

static int inside_board(int pos){ return pos>=0 && pos<64; }

static void promote_if_needed(GameState* g, int to){
    int r = row_of(to);
    uint64_t m = mask(to);
    if((g->p1 & m) && r==7){ g->p1 &= ~m; g->p1k |= m; }
    if((g->p2 & m) && r==0){ g->p2 &= ~m; g->p2k |= m; }
}

int try_move(GameState* g, int from, int to){
    if(!inside_board(from) || !inside_board(to)) return 0;
    if(!is_dark_square(from) || !is_dark_square(to)) return 0;
    if(square_occupied(g,to)) return 0;

    int moving_p1 = g->turn==1;
    if(moving_p1 && !is_p1_piece(g,from)) return 0;
    if(!moving_p1 && !is_p2_piece(g,from)) return 0;

    int dr = row_of(to) - row_of(from);
    int dc = col_of(to) - col_of(from);
    int adr = dr>0?dr:-dr, adc = dc>0?dc:-dc;
    if(adc != adr || (adr!=1 && adr!=2)) return 0;

    int isKing = is_king(g,from);
    if(!isKing){
        if(moving_p1 && dr<=0) return 0;
        if(!moving_p1 && dr>=0) return 0;
    }


    uint64_t fm = mask(from), tm = mask(to);


    if(adr==1){
        if(moving_p1){
            if(g->p1 & fm){ g->p1 &= ~fm; g->p1 |= tm; }
            else { g->p1k &= ~fm; g->p1k |= tm; }
        }else{
            if(g->p2 & fm){ g->p2 &= ~fm; g->p2 |= tm; }
            else { g->p2k &= ~fm; g->p2k |= tm; }
        }
        promote_if_needed(g,to);
        g->turn = moving_p1?2:1;
        return 1;
    }

    if(adr==2){
        int midr = (row_of(from)+row_of(to))/2;
        int midc = (col_of(from)+col_of(to))/2;
        int mid = midr*8 + midc;
        if(moving_p1 && !is_p2_piece(g,mid)) return 0;
        if(!moving_p1 && !is_p1_piece(g,mid)) return 0;

        if(moving_p1){
            if(g->p1 & fm){ g->p1 &= ~fm; g->p1 |= tm; }
            else { g->p1k &= ~fm; g->p1k |= tm; }
            uint64_t mm = mask(mid);
            g->p2 &= ~mm; g->p2k &= ~mm;
        }else{
            if(g->p2 & fm){ g->p2 &= ~fm; g->p2 |= tm; }
            else { g->p2k &= ~fm; g->p2k |= tm; }
            uint64_t mm = mask(mid);
            g->p1 &= ~mm; g->p1k &= ~mm;
        }
        promote_if_needed(g,to);
        g->turn = moving_p1?2:1;
        return 1;
    }

    return 0;
}

int has_winner(const GameState* g){
    int p1count = __builtin_popcountll(g->p1) + __builtin_popcountll(g->p1k);
    int p2count = __builtin_popcountll(g->p2) + __builtin_popcountll(g->p2k);
    if(p1count==0) return 2;
    if(p2count==0) return 1;
    return 0;
}

int current_player_can_move_simple(const GameState* g){
    const GameState* x=g;
    for(int from=0;from<64;from++){
        uint64_t m = 1ull<<from;
        int mine = (x->turn==1?((x->p1|x->p1k)&m):((x->p2|x->p2k)&m))!=0;
        if(!mine) continue;
        for(int to=0;to<64;to++){
            GameState temp=*x;
            if(try_move(&temp, from, to)) return 1;
        }
    }
    return 0;
}