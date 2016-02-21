#ifndef IOCONTROLLER_H_
#define IOCONTROLLER_H_


struct mazeGameSetup{
        int rows;
        int cols;
        int border;
        int wall;
        int player;
        int goal;
};

int start_maze_game(struct mazeGameSetup *);

#endif
