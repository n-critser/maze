#include<stdio.h>
#include"../graph/maze.h"
#include"../graph/grid.h"
#include"mazeFace.h"
#include "../constants/constants.h"

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
        
        build_grid(rows,cols);
        show_grid();
        destroy_grid();


        return 0;
}
