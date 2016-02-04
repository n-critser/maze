#include<stdio.h>
#include"../graph/maze.h"
#include"../graph/grid.h"
#include"mazeFace.h"
//#include "linuxList.h"

/* compile : gcc -Wall main.c grid.c */
/*  TODO: grid representation */

int main(int argc, char ** argv){
        int rows,cols;
        rows = 20;
        cols = 30;
        maze_play(cols,rows);
        
        build_grid(rows,cols);
        show_grid();
        destroy_grid();
        return 0;
}
