#include<stdio.h>
#include"maze.h"

/* compile : gcc -Wall main.c grid.c */
/*  TODO: grid representation */

int main(int argc, char ** argv){
        int rows,cols;
        rows = 20;
        cols = 30;
        
        build_grid(rows,cols);

        return 0;
}
