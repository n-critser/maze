#ifndef GRID_H_
#define GRID_H_

struct yxGrid {
        int rows;
        int cols;
        int **grid;
        int **maze;
        int dist_to_goal;
        char border;
        char wall;
        char player;
        char goal;
        struct pos{
                int y;
                int x;
        }current,goalPos,playerPos;
} ;

int build_grid(struct yxGrid *gridP);
void show_grid(struct yxGrid *gridP);
int destroy_grid(struct yxGrid *gridP);
struct yxGrid* init_grid(int,int,int,int,int,int);

struct vertex{
        int y;
        int x;
};

//struct yxGrid * gridP;

#endif
