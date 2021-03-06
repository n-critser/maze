#include<stdio.h>
#include<stdlib.h>
#include"../graph/maze.h"
#include"../graph/grid.h"
#include"mazeFace.h"
#include"ioController.h"
#include "../constants/constants.h"

//struct mazeGameSetup * gameSetup;

int print_setup(struct mazeGameSetup *setup){
        printf ( "setup->border char: %c\n",setup->border);
        printf ( "setup->wall char: %c\n",setup->wall);
        printf ( "setup->player char: %c\n",setup->player);
        printf ( "setup->goal char: %c\n",setup->goal);
        printf ( "setup->rows int: %d\n",setup->rows);
        printf ( "setup->cols int: %d\n",setup->cols);
        printf ("THATS IT FOR GAME SETUP\n");
        return 0;
}

int start_maze_game(struct mazeGameSetup *setup){

        /**maze_play should be moved to ioContoller
         * mazeFace : maze_game_init should be moved partially to ioController
         *            also should use build_grid to set
         *            so should have game_init call  grid_init , face_init ,   
         * grid ? maze ?  should be built from initialization
         * update maze in ioController
         * use maze to update face
         * should ioController be located in different directory (maybe mux) 
         */
        print_setup(setup);


        /* how does the face and the grid coincide?
         * 1. should build grid first. 
         * 2. show face
         * 3. start game loop
         * 4. get updates to grid
         * 5. update grid state
         * 6. update face
         * 7. get next input 
         */
        //      setup->rows,setup->cols,setup->player,setup->goal,setup->wall,setup->border
        // TODO: Remove these vars & assert on params
        int rows,cols,player,goal,wall,border;
        rows=setup->rows;
        cols=setup->cols;
        player=setup->player;
        goal=setup->goal;
        wall=setup->wall;
        border=setup->border;
        /* TODO:
           1. move play logic into ioController
           2.  update face with grid
           3. 
         */
        struct yxGrid * grid = init_grid(rows,cols,player,goal,wall,border);
        /* TODO:
           1. ADD mazeBuilder to graph package
           2. check for memory leaks
         */
        build_grid(grid);
        /* TODO:
           1. ADD MOVE list to yxGrid
           2. move show_grid to mazeFace
         */
        show_grid(grid);

        /* TODO:
           1. whats the minimum mazeFace needs  chars and int **
           2. score and level ... should move to game_setup
           3. update score and level inside grid.c ? or ioController
           4. ? gameState { score,level,moveString,...} agentState? 
         */
        maze_play(grid);        

        /*after all is done free memory */
        destroy_grid(grid);
        return 0;
}
