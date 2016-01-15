#include<stdio.h>
#include"../graph/maze.h"
#include"../graph/grid.h"
//#include "linuxList.h"

/* compile : gcc -Wall main.c grid.c */
/*  TODO: grid representation */

struct position {
        int y;
        int x;
} start;

int main(int argc, char ** argv){
        int rows,cols;
        rows = 20;
        cols = 30;
        
        build_grid(rows,cols);
        show_grid();
        destroy_grid();
        return 0;
}
