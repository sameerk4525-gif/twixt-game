#include <stdlib.h>   
#include "game.h"     

int kr[8] = { -2,-2,-1,-1, 1, 1, 2, 2 };
int kc[8] = { -1, 1,-2, 2,-2, 2,-1, 1 };

int seen[LIM][LIM];
int inside_board(const Game *g, int r, int c) {
    return (r >= 0 && r < g->size && c >= 0 && c < g->size);
}

void game_init(Game *g, int n) {
    if (n < 5)  n = 5;
    if (n > LIM) n = LIM;

    g->size   = n;
    g->eCount = 0;

    for (int i = 0; i < g->size; i++) {
        for (int j = 0; j < g->size; j++) {
            g->grid[i][j] = '.'; 
        }
    }

   
}

int segments_intersect(Pos p1, Pos p2, Pos p3, Pos p4) {
    
    int mid1_r = p1.r + p2.r;
    int mid1_c = p1.c + p2.c;

    int mid2_r = p3.r + p4.r;
    int mid2_c = p3.c + p4.c;

    if (mid1_r == mid2_r && mid1_c == mid2_c) {
      
        return 1;
    }
    return 0;
}

int edge_crosses(const Game *g, Pos a, Pos b) {
    for (int i = 0; i < g->eCount; i++) {
        Edge E = g->edges[i];

        
        if ((E.a.r == a.r && E.a.c == a.c) ||
            (E.a.r == b.r && E.a.c == b.c) ||
            (E.b.r == a.r && E.b.c == a.c) ||
            (E.b.r == b.r && E.b.c == b.c)) {
            continue;
        }

        if (segments_intersect(a, b, E.a, E.b)) {
            return 1; 
        }
    }
    return 0;
}
int edge_exists(const Game *g, Pos a, Pos b, int owner) {
    for (int i = 0; i < g->eCount; i++) {
        Edge E = g->edges[i];
        if (E.owner != owner) continue;

        int same_dir = (E.a.r == a.r && E.a.c == a.c &&
                        E.b.r == b.r && E.b.c == b.c);

        int flip_dir = (E.a.r == b.r && E.a.c == b.c &&
                        E.b.r == a.r && E.b.c == a.c);

        if (same_dir || flip_dir) return 1;
    }
    return 0;
}
void add_link(Game *g, Pos a, Pos b, int owner) {
    if (g->eCount >= LIM * 12) return;

    g->edges[g->eCount].a     = a;
    g->edges[g->eCount].b     = b;
    g->edges[g->eCount].owner = owner;
    g->eCount++;
}

void connect_knight_neighbours(Game *g, int r, int c, int owner) {
    Pos from = { r, c };

    for (int k = 0; k < 8; k++) {
        int nr = r + kr[k];
        int nc = c + kc[k];

        if (!inside_board(g, nr, nc)) continue;

        if (owner == RED && g->grid[nr][nc] != 'R') continue;
        if (owner == BLK && g->grid[nr][nc] != 'B') continue;

        Pos to = { nr, nc };

        if (edge_exists(g, from, to, owner)) continue;
        if (edge_crosses(g, from, to))       continue;

        add_link(g, from, to, owner);
    }
}


int game_place(Game *g, int row, int col, int player) {
    if (!inside_board(g, row, col))  return 0;
    if (g->grid[row][col] != '.')    return 0;

    g->grid[row][col] = (player == RED ? 'R' : 'B');
    connect_knight_neighbours(g, row, col, player);
    return 1;
}


void dfs_search(const Game *g, int r, int c, int player, int *found) {
    if (*found) return;

    seen[r][c] = 1;

    if (player == RED && r == g->size - 1) {
        *found = 1;
        return;
    }
    if (player == BLK && c == g->size - 1) {
        *found = 1;
        return;
    }

    for (int i = 0; i < g->eCount; i++) {
        Edge E = g->edges[i];
        if (E.owner != player) continue;

        Pos next;
        int use = 0;

        if (E.a.r == r && E.a.c == c) {
            next = E.b;
            use  = 1;
        } else if (E.b.r == r && E.b.c == c) {
            next = E.a;
            use  = 1;
        }

        if (use && !seen[next.r][next.c]) {
            dfs_search(g, next.r, next.c, player, found);
            if (*found) return;
        }
    }
}

int game_player_wins(Game *g, int player) {
   
    for (int i = 0; i < g->size; i++)
        for (int j = 0; j < g->size; j++)
            seen[i][j] = 0;

    int found = 0;

    if (player == RED) {
      
        for (int c = 0; c < g->size; c++) {
            if (g->grid[0][c] == 'R' && !seen[0][c]) {
                dfs_search(g, 0, c, player, &found);
                if (found) return 1;
            }
        }
    } else {
       
        for (int r = 0; r < g->size; r++) {
            if (g->grid[r][0] == 'B' && !seen[r][0]) {
                dfs_search(g, r, 0, player, &found);
                if (found) return 1;
            }
        }
    }

    return 0;
}


void game_cpu_move(Game *g, int player) {
    int rr[LIM * LIM];
    int cc[LIM * LIM];
    int n = 0;

    for (int r = 0; r < g->size; r++) {
        for (int c = 0; c < g->size; c++) {
            if (g->grid[r][c] == '.') {
                rr[n] = r;
                cc[n] = c;
                n++;
            }
        }
    }

    if (n == 0) return;

    int id = rand() % n;
    int r  = rr[id];
    int c  = cc[id];

    game_place(g, r, c, player);

    printf("Computer placed at %d %d\n", r + 1, c + 1);
}
