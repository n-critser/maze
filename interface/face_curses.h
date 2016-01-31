#include <stdio.h>
#include <ncurses.h>

#define MAX_WIDTH    200
#define MAX_HEIGHT   160


struct game_face{
        WINDOW *menu_win;
        WINDOW *maze;
        WINDOW *main;
};

struct win_pos{
        unsigned y;
        unsigned x;
};

int init_game(){
        struct game_face * game;
        /*how to you malloc WINDOW pointers */

        return -99;
}
