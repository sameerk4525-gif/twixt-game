#include "game.h"

void draw_ascii_link(char buf[LIM][LIM], const Edge *E, int size) {

    int r1 = E->a.r, c1 = E->a.c;
    int r2 = E->b.r, c2 = E->b.c;

    int dr = r2 - r1;
    int dc = c2 - c1;

    int steps = (dr < 0 ? -dr : dr);
    if (dc < 0 ? -dc : dc > steps) steps = (dc < 0 ? -dc : dc);
    if (steps < 1) return;

    char ch;
    if (dr == 0) ch = '-';
    else if (dc == 0) ch = '|';
    else if ((dr > 0 && dc > 0) || (dr < 0 && dc < 0)) ch = '\\';
    else ch = '/';

    for (int i = 1; i < steps; i++) {
       
        int rr = r1 + (dr * i) / steps;
        int cc = c1 + (dc * i) / steps;

        if (rr < 0 || rr >= size || cc < 0 || cc >= size) continue;
        if (buf[rr][cc] == 'R' || buf[rr][cc] == 'B')
            continue;

        buf[rr][cc] = ch;
    }
}

void game_draw_board(const Game *g) {
    char temp[LIM][LIM];

    for (int i = 0; i < g->size; i++)
        for (int j = 0; j < g->size; j++)
            temp[i][j] = g->grid[i][j];

    for (int i = 0; i < g->eCount; i++)
       draw_ascii_link(temp, &g->edges[i], g->size);

    printf("\n    ");
    for (int c = 1; c <= g->size; c++) printf("%2d ", c);
    printf("\n");

    for (int r = 0; r < g->size; r++) {
        printf("%2d | ", r + 1);
        for (int c = 0; c < g->size; c++) {
            char ch = temp[r][c];
            if (ch == 'R') {
                printf(C_RED "R" C_RST "  ");
            } else if (ch == 'B') {
                printf(C_BLUE "B" C_RST "  ");
            } else {
                printf("%c  ", ch);
            }
        }
        printf("\n");
    }
    printf("\nLegend: R = Red peg, B = Black peg, - | / \\ = links\n\n");
}
