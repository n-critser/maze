#include<stdio.h>
#include<stdlib.h>
#include"../graph/maze.h"
#include"../graph/grid.h"
#include"mazeFace.h"
#include"ioController.h"
#include "../constants/constants.h"

//struct mazeGameSetup * gameSetup;

int start_maze_game(int rows, int cols){

        /**maze_play should be moved to ioContoller
         * mazeFace : maze_game_init should be moved partially to ioController
         *            also should use build_grid to set
         *            so should have game_init call  grid_init , face_init ,   
         * grid ? maze ?  should be built from initialization
         * update maze in ioController
         * use maze to update face
         * should ioController be located in different directory (maybe mux) 
         */
        maze_play(cols,rows);

        /* how does the face and the grid coincide?
         * 1. should build grid first. 
         * 2. show face
         * 3. start game loop
         * 4. get updates to grid
         * 5. update grid state
         * 6. update face
         * 7. get next input 
         */
        struct mazeGameSetup *gameSetup=malloc(sizeof(struct mazeGameSetup));
        gameSetup->border='!';
        gameSetup->wall='*';
        gameSetup->player='@';
        gameSetup->goal='#';
        gameSetup->rows=rows;
        gameSetup->cols=cols;
        int border='!';
        int wall='*';
        int player='@';
        int goal='#';
        build_grid(rows,cols,player,goal,wall,border);
        show_grid();
        destroy_grid();
        free(gameSetup);

        return 0;
}
