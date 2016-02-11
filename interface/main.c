#include<stdio.h>
#include"ioController.h"

/* compile : gcc -Wall main.c grid.c */
/*  TODO: grid representation */

int main(int argc, char ** argv){
        int rows,cols;
        rows = 20;
        cols = 30;

        int retVal=-1;
        retVal= start_maze_game(rows,cols);
        return retVal;
}
