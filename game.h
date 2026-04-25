#ifndef TWIXT_GAME_H
#define TWIXT_GAME_H

#include <stdio.h>

#define LIM 25
#define RED 1
#define BLK 2

typedef struct {
    int r, c;
} Pos;

typedef struct {
    Pos a, b;
    int owner;  
} Edge;

typedef struct {
    int size;
    char grid[LIM][LIM];   
    Edge edges[LIM * 12];
    int eCount;

    
    Pos moveStack[LIM * LIM];
    int moveTop;

} Game;

#define C_RED   "\x1b[31m"
#define C_BLUE  "\x1b[34m"
#define C_RST   "\x1b[0m"

void game_init(Game *g, int n);
int  game_place(Game *g, int row, int col, int player);
int  game_player_wins(Game *g, int player);
void game_cpu_move(Game *g, int player);
void game_draw_board(const Game *g);
void game_undo(Game *g);   

int  inside_board(const Game *g, int r, int c);

#endif
