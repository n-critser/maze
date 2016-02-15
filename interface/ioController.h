#ifndef IOCONTROLLER_H_
#define IOCONTROLLER_H_

int start_maze_game(int rows, int cols);

struct mazeGameSetup{
        int rows;
        int cols;
        int border;
        int wall;
        int player;
        int goal;
};

#endif
