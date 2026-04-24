#include <stdio.h>
#include "game.h"

int main(void) {
    Game g;
    int mode;

    printf("Board size (5 to 25): ");
    if (scanf("%d", &g.size) != 1) return 0;
    game_init(&g, g.size);

    printf("1 - Player vs Player\n2 - Player vs Computer (You = RED)\nChoice: ");
    if (scanf("%d", &mode) != 1) return 0;
    if (mode != 1 && mode != 2) mode = 1;

    int turn = RED;

    while (1) {

        game_draw_board(&g);

        int r, c;

        if (mode == 2 && turn == BLK) {
            game_cpu_move(&g, turn);
        } else {
            if (turn == RED)
                printf("Red move (row col, 0 0 quits): ");
            else
                printf("Black move (row col, 0 0 quits): ");

            if (scanf("%d %d", &r, &c) != 2) break;

            if (r == 0 && c == 0) {
                printf("Game ended.\n");
                break;
            }

            if (r < 1 || r > g.size || c < 1 || c > g.size) {
                printf("Invalid.\n");
                continue;
            }

            if (!game_place(&g, r - 1, c - 1, turn)) {
                printf("That spot is used.\n");
                continue;
            }
        }

        if (game_player_wins(&g, turn)) {
            game_draw_board(&g);
            if (turn == RED) printf("RED wins!\n");
            else             printf("BLACK wins!\n");
            break;
        }

        turn = (turn == RED ? BLK : RED);
    }

    return 0;
}
