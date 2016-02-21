#include<stdio.h>
#include<stdlib.h>
#include"ioController.h"

/* compile : gcc -Wall main.c grid.c */
/*  TODO: grid representation */

int main(int argc, char ** argv){
        int rows,cols;
        rows = 20;
        cols = 30;
        struct mazeGameSetup *gameSetup=malloc(sizeof(struct mazeGameSetup));
        gameSetup->border='!';
        gameSetup->wall='*';
        gameSetup->player='@';
        gameSetup->goal='#';
        gameSetup->rows=rows;
        gameSetup->cols=cols;
        int retVal=-1;
        retVal= start_maze_game(gameSetup);
        free(gameSetup);
        return retVal;
}
